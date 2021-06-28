#include "ProtocolHandler.h"

//#define DEBUG_LOG

#ifdef DEBUG_LOG
#include <QDebug>
#endif


ProtocolHandler::ProtocolHandler(QObject *parent) : QObject(parent)
{
    // Handle rx & tx data
    QObject::connect(&timer, &QTimer::timeout, this, &ProtocolHandler::handle);
    timer.setInterval(PACKET_HANDLE_TIMEOUT_MS);
    timer.start();
}

void ProtocolHandler::addTxRawData(QByteArray data)
{
#ifdef DEBUG_LOG
    qDebug() << Qt::endl << __PRETTY_FUNCTION__;
    qDebug() << data;
#endif

    txRawData.append(data);
}

uint8_t ProtocolHandler::calculateCRC(const QByteArray &data)
{
    uint8_t crc = 0x00;

    for (uint8_t byte : data)
    {
        for (uint8_t tempI = 8; tempI; tempI--)
        {
            uint8_t sum = (crc ^ byte) & 0x01;
            crc >>= 1;
            if (sum)
            {
                crc ^= 0x8C;
            }
            byte >>= 1;
        }
    }

    return crc;
}

void ProtocolHandler::onReceived(QByteArray bytes)
{
#ifdef DEBUG_LOG
    qDebug() << Qt::endl << __PRETTY_FUNCTION__;
    qDebug() << bytes;
#endif

    rxPackets.push_back(bytes);
}

void ProtocolHandler::handle()
{
    // Parse incoming data into packets
    handleRxPackets();


    if (rxRawData.count() > 0)
    {
    emit received(rxRawData);
    rxRawData.clear();
    }

    // Compose packets from the outgoing data
    handleTxPackets();
}

void ProtocolHandler::handleRxPackets()
{

    QByteArray packet;

    bool stx = false;
    bool etx = false;
    bool dle = false;
    int parsedOffset = 0;
    int currentOffset = 0;


    for (const auto &byte : qAsConst(rxPackets))
    {
        currentOffset++;

        // Packet start flag
        if (!stx)
        {
            stx = Protocol::STX == (uint8_t)byte && !dle;
            if (stx)
            {
                packet.clear();
                continue;
            }
        }

        // Packet end flag
        if (!etx)
        {
            etx = Protocol::ETX == (uint8_t)byte && stx && !dle;
            if (etx)
            {
                if (packet.size() > 1)
                {
                    // Last packet byte is the CS value
                    // Packet escape flags is not included in CRC
                    //uint8_t cs = packet.back();
                    //packet.chop(1);

                    //if (cs == calculateCRC(packet))
                    //{
                        // A valid packet is found
                        // TODO: Data should be further parsed
#ifdef DEBUG_LOG
                        qDebug() << "Parsed: " << QString::number(packet.at(0));
#endif

                       rxRawData.enqueue(packet);
                    //}
                }

                parsedOffset = currentOffset;
                stx = false;
                etx = false;
                continue;
            }
        }

        // Packet escape flag
        dle = Protocol::DLE == (uint8_t)byte && !dle;
        if (dle)
        {
            continue;
        }

        // Packet data
        if (stx)
        {
            packet.push_back(byte);
        }
    }

    // Remove already proccessed raw data
    rxPackets.remove(0, parsedOffset);

//#ifdef DEBUG_LOG
//    if (!packet.isEmpty())
//    {
//        qDebug() << Qt::Qt::endl << __PRETTY_FUNCTION__;
//        qDebug() << rawRxData;
//        qDebug() << packet;
//    }
//#endif

}

void ProtocolHandler::handleTxPackets()
{
    // Compose tx packets
    while (!txRawData.empty())
    {
        QByteArray packet;
        QByteArray bytes = txRawData.dequeue();

        // Escape any special bytes in the raw tx data
        for(const auto &byte : bytes)
        {
            if (Protocol::STX == (uint8_t)byte || Protocol::ETX == (uint8_t)byte || Protocol::DLE == (uint8_t)byte)
            {
                packet.append(Protocol::DLE);
            }
            packet.append(byte);
        }

        //packet.append(calculateCRC(packet));
        packet.prepend(Protocol::STX);
        packet.append(Protocol::ETX);

        txPackets.append(packet);
    }

    // TODO: Refactor
    // Send tx packets to the underlying communication hardware
//    while(!txPackets.empty())
//    {
//        emit send(txPackets.dequeue());
//    }

    if (!txPackets.empty())
    {
        emit send(txPackets.dequeue());
    }
}
