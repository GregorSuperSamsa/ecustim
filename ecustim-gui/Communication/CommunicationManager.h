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
    Q_INVOKABLE void connect(const QString& connectionInfo = "");
    Q_INVOKABLE void disconnect();

private:
    QScopedPointer<Communication> communicator;

    // Current connection type
    CONNECTION_TYPE connectionType_ = CONNECTION_TYPE_UNKNOWN;

    QVector<QSharedPointer<Model>> models;

signals:
    void triggerSamples(QByteArray samples);
    void connectionTypeChanged(CONNECTION_TYPE connectionType);
    void remoteDeviceModelChanged();
    //
    void remoteDeviceDiscoveryStarted();
    void remoteDeviceDiscoveryFinished();

public slots:
    void setConnectionType(CONNECTION_TYPE connectionType);
    void startRemoteDeviceDiscovery();
    void stopRemoteDeviceDiscovery();
    void onRemoteDeviceDiscovered(QSharedPointer<RemoteDeviceItem> item);
    void onRemoteDeviceConnected(QString connectionInfo);
    void onRemoteDeviceDisconnected(QString connectionInfo);

};

#endif // COMMUNICATION_MANAGER_H
