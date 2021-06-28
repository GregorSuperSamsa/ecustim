#ifndef DEVICEITEM_H
#define DEVICEITEM_H

#include <QObject>

class RemoteDeviceItem : public QObject
{
    Q_OBJECT

    Q_PROPERTY(CONNECTHardwareManagerN_STATE connectionState READ connectionState WRITE setConnectionState NOTIFY connectionStateChanged);
    Q_PROPERTY(QString displayText READ displayText WRITE setDisplayText NOTIFY displayTextChanged)
    Q_PROPERTY(QString connectionString READ connectionString WRITE setConnectionString NOTIFY connectionStringChanged)
    Q_PROPERTY(QStringList additionalInfo READ additionalInfo WRITE setAdditionalInfo NOTIFY additionalInfoChanged)

public:
    explicit RemoteDeviceItem(QObject *parent = nullptr);

    //
    enum CONNECTHardwareManagerN_STATE
    {
        //CONNECTING = 0,
        CONNECTED,
        //DISCONNECTING,
        UNCONNECTED,
        //UNKNOWN,
    };
    Q_ENUM(CONNECTHardwareManagerN_STATE)

    QStringList additionalInfo() const
    {
        return m_additionalInfo;
    }

    QString displayText() const
    {
        return m_displayText;
    }

    QString connectionString() const
    {
        return m_connectionString;
    }

    CONNECTHardwareManagerN_STATE connectionState() const
    {
        return m_connectionState;
    }

private:
    QString m_displayText;
    QStringList m_additionalInfo;
    QString m_connectionString;
    CONNECTHardwareManagerN_STATE m_connectionState = UNCONNECTED;

public slots:

    void setAdditionalInfo(QStringList additionalInfo)
    {
        if (m_additionalInfo == additionalInfo)
            return;

        m_additionalInfo = additionalInfo;
        emit additionalInfoChanged(m_additionalInfo);
    }

    void setDisplayText(QString displayText)
    {
        if (m_displayText == displayText)
            return;

        m_displayText = displayText;
        emit displayTextChanged(m_displayText);
    }

    void setConnectionString(QString connectionString)
    {
        if (m_connectionString == connectionString)
            return;

        m_connectionString = connectionString;
        emit connectionStringChanged(m_connectionString);
    }

    void setConnectionState(CONNECTHardwareManagerN_STATE connectionState)
    {
        if (m_connectionState == connectionState)
            return;

        m_connectionState = connectionState;
        emit connectionStateChanged(m_connectionState);
    }

signals:
    void additionalInfoChanged(QStringList additionalInfo);
    void displayTextChanged(QString displayText);
    void connectionStringChanged(QString connectionString);
    void connectionStateChanged(CONNECTHardwareManagerN_STATE connectionState);
};

#endif // DEVICEITEM_H
