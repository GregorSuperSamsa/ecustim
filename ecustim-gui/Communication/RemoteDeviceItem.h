#ifndef DEVICEITEM_H
#define DEVICEITEM_H

#include <QObject>

class RemoteDeviceItem : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool connected READ connected WRITE setConnectede NOTIFY connectedChanged)
    Q_PROPERTY(QString displayText READ displayText WRITE setDisplayText NOTIFY displayTextChanged)
    Q_PROPERTY(QString connectionString READ connectionString WRITE setConnectionString NOTIFY connectionStringChanged)
    Q_PROPERTY(QStringList additionalInfo READ additionalInfo WRITE setAdditionalInfo NOTIFY additionalInfoChanged)

    QString m_displayText;
    QStringList m_additionalInfo;
    QString m_connectionString;

    bool m_connected;

public:
    explicit RemoteDeviceItem(QObject *parent = nullptr);

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

    bool connected() const
    {
        return m_connected;
    }

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

    void setConnectede(bool connected)
    {
        if (m_connected == connected)
            return;

        m_connected = connected;
        emit connectedChanged(m_connected);
    }

signals:
    void additionalInfoChanged(QStringList additionalInfo);
    void displayTextChanged(QString displayText);
    void connectionStringChanged(QString connectionString);
    void connectedChanged(bool connected);
};

#endif // DEVICEITEM_H
