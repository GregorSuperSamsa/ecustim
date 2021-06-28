#ifndef PROTOCOLHANDLER_H
#define PROTOCOLHANDLER_H

#include <QObject>
#include <QQueue>
#include <QTimer>
#include "Protocol.h"

class ProtocolHandler: public QObject
{
    Q_OBJECT

public:
    explicit ProtocolHandler(QObject *parent = nullptr);

    void addTxRawData(QByteArray data);

private:
    static const  int PACKET_HANDLE_TIMEOUT_MS = 20;
    QTimer timer;

    // Raw binary data pending to be formated as tx packets
    QQueue<QByteArray> txRawData;
    // Tx packets ready to be sent
    QQueue<QByteArray> txPackets;

    // Raw binary data extracted from the rx packets
    QQueue<QByteArray> rxRawData;
    // Rx packets ready to be parsed
    QByteArray rxPackets;



    uint8_t calculateCRC(const QByteArray& data);

    void handleRxPackets();
    void handleTxPackets();

public slots:
    void onReceived(QByteArray bytes);
    void handle();

signals:
    void send(QByteArray bytes);
    void received(QQueue<QByteArray>);
};

#endif // PROTOCOLHANDLER_H
