#include "TriggerGenerator.h"
#include <QDebug>
#include <QtCharts/QValueAxis>
#include <QtCharts/QXYSeries>


Q_DECLARE_METATYPE(QtCharts::QAbstractSeries *)
Q_DECLARE_METATYPE(QtCharts::QAbstractAxis *)


TriggerGenerator::TriggerGenerator(QSharedPointer<CommunicationManager> communicator, QObject *parent) : QObject(parent),
    communicator(communicator)
{
    QObject::connect(communicator.data(), &CommunicationManager::triggerSamples, this, &TriggerGenerator::onTriggerSamples);


    patterns_ << "1: 4 cylinder dizzy";
    patterns_ << "2: 6 cylinder dizzy";
    patterns_ << "3: 8 cylinder dizzy";
    patterns_ << "4: 60-2 crank only";
    patterns_ << "5: 60-2 crank and cam";
    patterns_ << "6: 36-1 crank only";
    patterns_ << "7: 4-1 crank wheel with cam";
    patterns_ << "8: 8-1 crank only (R6)";
    patterns_ << "9: 6-1 crank with cam";
    patterns_ << "10: 12-1 crank with cam";
    patterns_ << "11: 40-1 crank only (Ford V10)";
    patterns_ << "12: Distributor style 4 cyl 50deg off, 40 deg on";
    patterns_ << "13: odd fire 90 deg pattern 0 and 135 pulses";
    patterns_ << "14: GM OptiSpark LT1 360 and 8";
    patterns_ << "15: 12-3 oddball";
    patterns_ << "16: 36-2-2-2 Crank only";
    patterns_ << "17: 36-2-2-2 Crank and cam";
    patterns_ << "18: GM 4200 crank wheel";
    patterns_ << "19: Mazda FE3 36-1 with cam";
    patterns_ << "20: Mitsubishi 6g72 with cam";
    patterns_ << "21: Buell Oddfire CAM wheel";
    patterns_ << "22: GM LS1 crank and cam";
    patterns_ << "23: Odd Lotus 36-1-1-1-1 flywheel";
    patterns_ << "24: Honda RC51 with cam";
    patterns_ << "25: 36-1 crank with 2nd trigger on teeth 33-34";
    patterns_ << "26: 36-1+1 crank with cam pattern NGC4";
    patterns_ << "27: Weber-Marelli 8 crank+2 cam pattern";
    patterns_ << "28: Fiat 1.8 16V crank and cam";
    patterns_ << "29: Nissan 360 CAS with 6 slots";
    patterns_ << "30: Mazda CAS 24-2 with single pulse outer ring";
    patterns_ << "31: Yamaha 2002-03 R1 8 even-tooth crank with 1 tooth cam";
    patterns_ << "32: GM 4 even-tooth crank with 1 tooth cam";
    patterns_ << "33: GM 6 even-tooth crank with 1 tooth cam";
    patterns_ << "34: GM 8 even-tooth crank with 1 tooth cam";
    patterns_ << "35: Volvo d12[acd] crank with 7 tooth cam";
    patterns_ << "36: Mazda 36-2-2-2 with 6 tooth cam";
    patterns_ << "37: GM 60-2 with 4X cam";
    patterns_ << "38: Dodge Viper Gen IV SRT V10 60-2 with 5 tooth cam";
    patterns_ << "39: Suzuki GSX-1300R 24-1 crank and 1 tooth cam during missing crank tooth";
    patterns_ << "40: Mitsubishi & Mazda 4g63 with cam";

    patternsChanged();

}

void TriggerGenerator::onTriggerSamples(QByteArray samples)
{
    samples_camshaft.clear();
    samples_crankshaft.clear();

    int x = 0;
    for (auto sample : samples)
    {
        //
        float crank = sample & 0x01;
        float cam = sample >> 1;
        if (cam == 1)
            cam -= 0.1;
        else cam += 0.1;

        //1
        samples_crankshaft.append(QPointF(x, crank));
        samples_camshaft.append(QPointF(x, cam));
        x++;
        //2
        samples_crankshaft.append(QPointF(x, crank));
        samples_camshaft.append(QPointF(x, cam));
        x++;
        //3
        samples_crankshaft.append(QPointF(x, crank));
        samples_camshaft.append(QPointF(x, cam));
        x++;
        //4
        samples_crankshaft.append(QPointF(x, crank));
        samples_camshaft.append(QPointF(x, cam));


    }

    setAxisXCount(x);

    emit updatePending();
    qDebug() << "Samples count: " << samples_crankshaft.count();

}

void TriggerGenerator::updateSamplesCount(QtCharts::QAbstractAxis *axis)
{
    if (axis)
    {
        QtCharts::QValueAxis *xAxis = static_cast<QtCharts::QValueAxis *>(axis);
        //xAxis->setMin(0);
        xAxis->setMax(samples_camshaft.count());
    }
}

void TriggerGenerator::updateCamSamples(QtCharts::QAbstractSeries *series)
{
    if (series) {
        QtCharts::QXYSeries *xySeries = static_cast<QtCharts::QXYSeries *>(series);
        xySeries->replace(samples_camshaft);
        // xySeries->setVisible(false);
    }
}



void TriggerGenerator::updateCrankSamples(QtCharts::QAbstractSeries *series)
{
    if (series) {
        QtCharts::QXYSeries *xySeries = static_cast<QtCharts::QXYSeries *>(series);
        xySeries->replace(samples_crankshaft);
    }
}

void TriggerGenerator::setAxisXCount(int count)
{
    if (count != axis_x_count)
    {
        axis_x_count = count;
        emit axisXCountChanged(axis_x_count);
    }
}

int TriggerGenerator::axisXCount() const
{
    return  axis_x_count;
}
