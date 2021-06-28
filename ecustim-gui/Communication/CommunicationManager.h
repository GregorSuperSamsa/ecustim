#ifndef COMMUNICATHardwareManagerN_MANAGER_H
#define COMMUNICATHardwareManagerN_MANAGER_H

#include <QObject>
#include <QScopedPointer>
#include <QTimer>
#include <QQueue>
#include "Bluetooth.h"
#include "Uart.h"
#include "UI/Model.h"


class CommunicationManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(Model* remoteDeviceModel READ remoteDeviceModel NOTIFY remoteDeviceModelChanged)
    Q_PROPERTY(CONNECTION_TYPE connectionType READ connectionType WRITE setConnectionType NOTIFY connectionTypeChanged);

public:
    explicit CommunicationManager(QObject *parent = nullptr);

    Model* remoteDeviceModel() const;

    //
    enum CONNECTION_TYPE
    {
        BLUETOOTH = 0,
        USB_UART,
        CONNECTION_TYPE_UNKNOWN,
        CONNECTION_TYPE_COUNT,
    };
    Q_ENUM(CONNECTION_TYPE)
    CONNECTION_TYPE connectionType() const;
    //
    Q_INVOKABLE void connect(const QString& connectionInfo = "");
    Q_INVOKABLE void disconnect();

    void send(const QByteArray& data);
    void sendRaw(const QByteArray& rawData);

private:
    QScopedPointer<Communication> _communicator;

    static const  int PACKET_HANDLE_TIMEOUT_MS = 20;
    QTimer _timer;

    QQueue<QByteArray> txPackets;
    QByteArray rxBuffer;

    // Current connection type
    CONNECTION_TYPE _connectionType = CONNECTION_TYPE_UNKNOWN;

    QVector<QSharedPointer<Model>> _models;

    QByteArray composeTxPacket(const QByteArray &data) const;

signals:
    void connectionTypeChanged(CONNECTION_TYPE connectionType);
    void remoteDeviceModelChanged();
    //
    void remoteDeviceDiscoveryStarted();
    void remoteDeviceDiscoveryFinished();
    //
    void received(QByteArray data);

private slots:
    void onTimeout();

public slots:
    void onReceived(QByteArray data);

    void setConnectionType(CONNECTION_TYPE connectionType);
    void startRemoteDeviceDiscovery();
    void stopRemoteDeviceDiscovery();
    void onRemoteDeviceDiscovered(QSharedPointer<RemoteDeviceItem> item);
    void onRemoteDeviceConnected(QString connectionInfo);
    void onRemoteDeviceDisconnected(QString connectionInfo);

};

#endif // COMMUNICATHardwareManagerN_MANAGER_H
