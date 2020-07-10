#ifndef COMMUNICATION_MANAGER_H
#define COMMUNICATION_MANAGER_H

#include <QObject>
#include <QScopedPointer>
#include "Communication/Bluetooth/Bluetooth.h"
#include "Communication/Uart/Uart.h"
#include "UI/Model.h"


class CommunicationManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(Model* remoteDeviceModel READ remoteDeviceModel NOTIFY remoteDeviceModelChanged)
    Q_PROPERTY(CONNECTION_TYPE connectionType READ connectionType WRITE setConnectionType NOTIFY connectionTypeChanged);
    Q_PROPERTY(CONNECTION_STATUS connectionStatus READ connectionStatus WRITE setConnectionStatus NOTIFY connectionStatusChanged);

public:
    explicit CommunicationManager(QObject *parent = nullptr);
    void send(const QByteArray& data);

    Model* remoteDeviceModel() const;

    //
    enum CONNECTION_TYPE
    {
        BLUETOOTH = 0,
        USB_UART,
        CONNECTION_TYPE_UNKNOWN,
        CONNECTION_TYPE_COUNT
    };
    Q_ENUM(CONNECTION_TYPE)
    CONNECTION_TYPE connectionType() const;

    //
    enum CONNECTION_STATUS
    {
        IDLE,
        DISCOVERY_STARTED,
        DISCOVERY_FINISHED,
        CONNECTING_STARTED,
        CONNECTED,
        NOT_CONNECTED,
        CONNECTION_STATUS_UNKNOWN,
        CONNECTION_STATUS_COUNT
    };
    Q_ENUM(CONNECTION_STATUS)
    CONNECTION_STATUS connectionStatus() const;

    //
    Q_INVOKABLE void connect(const QString& connectionInfo = "");

private:
    QScopedPointer<Communication> communicator;

    // Current connection type
    CONNECTION_TYPE connectionType_ = CONNECTION_TYPE_UNKNOWN;
    // Current connection status
    CONNECTION_STATUS connectionStatus_ = CONNECTION_STATUS_UNKNOWN;;

    QVector<QSharedPointer<Model>> models;

signals:
    void triggerSamples(QByteArray samples);
    void connectionTypeChanged(CONNECTION_TYPE connectionType);
    void remoteDeviceModelChanged();

    void connectionStatusChanged(CONNECTION_STATUS connectionStatus);

public slots:
    void setConnectionType(CONNECTION_TYPE connectionType);
    void setConnectionStatus(CONNECTION_STATUS connectionStatus);
    void findDevices();
    void onRemoteDeviceDiscovered(QSharedPointer<RemoteDeviceItem> item);
    void onRemoteDeviceDiscoveryFinished();

};

#endif // COMMUNICATION_MANAGER_H
