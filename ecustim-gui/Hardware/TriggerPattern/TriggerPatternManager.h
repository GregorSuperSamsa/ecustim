#ifndef TRIGGER_PATTERN_MANAGER
#define TRIGGER_PATTERN_MANAGER

#include <QObject>
#include <QSharedPointer>
#include <QtCharts/QAbstractSeries>
#include <QtCharts/QAbstractAxis>
#include <QStringList>
#include "Communication/CommunicationManager.h"
#include "UI/Model.h"


class TriggerPatternManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Model* model READ model CONSTANT)
    Q_PROPERTY(int axisXCount READ axisXCount WRITE setAxisXCount NOTIFY axisXCountChanged)

public:
    explicit TriggerPatternManager(QSharedPointer<CommunicationManager> communicator, QObject *parent = nullptr);

    Model* model() const;

private:
    Model* model_;

    QSharedPointer<CommunicationManager> communicator;
    QVector<QPointF> samples_crankshaft;
    QVector<QPointF> samples_camshaft;

    void initTestData();

    void setAxisXCount(int count);
    int axisXCount() const;

    int axis_x_count;

signals:
    void updatePending();
    void axisXCountChanged(int count);

public slots:
    void onTriggerSamples(QByteArray samples);
    void updateCamSamples(QtCharts::QAbstractSeries *series);
    void updateCrankSamples(QtCharts::QAbstractSeries *series);
    void updateSamplesCount(QtCharts::QAbstractAxis *axis);
};

#endif // TRIGGER_PATTERN_MANAGER
