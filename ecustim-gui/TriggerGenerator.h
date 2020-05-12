#ifndef TRIGGERGENERATOR_H
#define TRIGGERGENERATOR_H

#include <QObject>
#include <QSharedPointer>
#include <QtCharts/QAbstractSeries>
#include <QtCharts/QAbstractAxis>
#include <QStringList>
#include "Communicator.h"


class TriggerGenerator : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int axisXCount READ axisXCount WRITE setAxisXCount NOTIFY axisXCountChanged)
    Q_PROPERTY(QStringList patterns MEMBER patterns_ NOTIFY patternsChanged)

public:
    explicit TriggerGenerator(QSharedPointer<Communicator> communicator, QObject *parent = nullptr);

private:
    QSharedPointer<Communicator> communicator;
    QVector<QPointF> samples_crankshaft;
    QVector<QPointF> samples_camshaft;


    void setAxisXCount(int count);
    int axisXCount() const;

    int axis_x_count;
    QStringList patterns_;

signals:
    void updatePending();
    void axisXCountChanged(int count);
    void patternsChanged();

public slots:
    void onTriggerSamples(QByteArray samples);
    void updateCamSamples(QtCharts::QAbstractSeries *series);
    void updateCrankSamples(QtCharts::QAbstractSeries *series);
    void updateSamplesCount(QtCharts::QAbstractAxis *axis);
};

#endif // TRIGGERGENERATOR_H
