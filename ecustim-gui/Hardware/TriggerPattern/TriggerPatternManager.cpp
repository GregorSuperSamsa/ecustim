#include "TriggerPatternManager.h"
#include "TriggerPatternItem.h"
#include <QDebug>
#include <QtCharts/QValueAxis>
#include <QtCharts/QXYSeries>


Q_DECLARE_METATYPE(QtCharts::QAbstractSeries *)
Q_DECLARE_METATYPE(QtCharts::QAbstractAxis *)


TriggerPatternManager::TriggerPatternManager(QSharedPointer<CommunicationManager> communicator, QObject *parent) : QObject(parent),
    model_(new Model(this)),
    communicator(communicator)
{
    initTestData();

    QObject::connect(communicator.data(), &CommunicationManager::triggerSamples, this, &TriggerPatternManager::onTriggerSamples);

}

Model *TriggerPatternManager::model() const
{
    return  model_;
}

void TriggerPatternManager::onTriggerSamples(QByteArray samples)
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

void TriggerPatternManager::updateSamplesCount(QtCharts::QAbstractAxis *axis)
{
    if (axis)
    {
        QtCharts::QValueAxis *xAxis = static_cast<QtCharts::QValueAxis *>(axis);
        //xAxis->setMin(0);
        xAxis->setMax(samples_camshaft.count());
    }
}

void TriggerPatternManager::updateCamSamples(QtCharts::QAbstractSeries *series)
{
    if (series) {
        QtCharts::QXYSeries *xySeries = static_cast<QtCharts::QXYSeries *>(series);
        xySeries->replace(samples_camshaft);
        // xySeries->setVisible(false);
    }
}

void TriggerPatternManager::updateCrankSamples(QtCharts::QAbstractSeries *series)
{
    if (series) {
        QtCharts::QXYSeries *xySeries = static_cast<QtCharts::QXYSeries *>(series);
        xySeries->replace(samples_crankshaft);
    }
}

void TriggerPatternManager::setAxisXCount(int count)
{
    if (count != axis_x_count)
    {
        axis_x_count = count;
        emit axisXCountChanged(axis_x_count);
    }
}

int TriggerPatternManager::axisXCount() const
{
    return  axis_x_count;
}


void TriggerPatternManager::initTestData()
{
    {
        QSharedPointer<TriggerPatternItem> item(new TriggerPatternItem(this));
        item->setName("1: 4 cylinder dizzy");


        QVector<int> i = { /* dizzy 4 cylinder */
                           1,0,1,0 /* two pulses per crank revolution (one per cylinder) */
                         };
//        const unsigned char dizzy_four_cylinder[]  =
//        { /* dizzy 4 cylinder */
//          1,0,1,0 /* two pulses per crank revolution (one per cylinder) */
//        };
//        QByteArray b(reinterpret_cast<const char*>(dizzy_four_cylinder) ,
//                     sizeof(dizzy_four_cylinder));

        item->setData(i);
        model_->insert(item);

    }

    {
        QSharedPointer<TriggerPatternItem> item(new TriggerPatternItem(this));
        item.reset(new TriggerPatternItem(this));
        item->setName("2: 6 cylinder dizzy");

        QVector<int> i = {
                            0,0,3,0,0,3,0,0,1,  /* Teeth 1-3 */
                            0,0,1,0,0,1,0,0,0,  /* Teeth 4 and 5 and MISSING 6th */
                            0,0,1,0,0,1,2,2,1,  /* 2nd rev teeth 7 and 8, then 2nd trigger on cam between 8 and 9 */
                            0,0,1,0,0,1,0,0,0   /* teeth 10 and 11 then missing 12th */
                        };

        //        var rotationDegrees = 360

        item->setData(i);
        model_->insert(item);
    }

    return;
    {
        QSharedPointer<TriggerPatternItem> item(new TriggerPatternItem(this));
        item->setName("3: 8 cylinder dizzy");
        model_->insert(item);
    }
    {
        QSharedPointer<TriggerPatternItem> item(new TriggerPatternItem(this));
        item->setName("4: 60-2 crank only");
        model_->insert(item);
    }
    {
        QSharedPointer<TriggerPatternItem> item(new TriggerPatternItem(this));
        item->setName("5: 60-2 crank and cam");
        model_->insert(item);
    }
    {
        QSharedPointer<TriggerPatternItem> item(new TriggerPatternItem(this));
        item->setName("6: 36-1 crank only");
        model_->insert(item);
    }
    {
        QSharedPointer<TriggerPatternItem> item(new TriggerPatternItem(this));
        item->setName("7: 4-1 crank wheel with cam");
        model_->insert(item);
    }
    {
        QSharedPointer<TriggerPatternItem> item(new TriggerPatternItem(this));
        item->setName("8: 8-1 crank only (R6)");
        model_->insert(item);
    }
    {
        QSharedPointer<TriggerPatternItem> item(new TriggerPatternItem(this));
        item->setName("9: 6-1 crank with cam");
        model_->insert(item);
    }
    {
        QSharedPointer<TriggerPatternItem> item(new TriggerPatternItem(this));
        item->setName("10: 12-1 crank with cam");
        model_->insert(item);
    }
    {
        QSharedPointer<TriggerPatternItem> item(new TriggerPatternItem(this));
        item->setName("11: 40-1 crank only (Ford V10)");
        model_->insert(item);
    }
    {
        QSharedPointer<TriggerPatternItem> item(new TriggerPatternItem(this));
        item->setName("12: Distributor style 4 cyl 50deg off, 40 deg on");
        model_->insert(item);
    }
    {
        QSharedPointer<TriggerPatternItem> item(new TriggerPatternItem(this));
        item->setName("13: odd fire 90 deg pattern 0 and 135 pulses");
        model_->insert(item);
    }
    {
        QSharedPointer<TriggerPatternItem> item(new TriggerPatternItem(this));
        item->setName("14: GM OptiSpark LT1 360 and 8");
        model_->insert(item);
    }
    {
        QSharedPointer<TriggerPatternItem> item(new TriggerPatternItem(this));
        item->setName("15: 12-3 oddball");
        model_->insert(item);
    }
    {
        QSharedPointer<TriggerPatternItem> item(new TriggerPatternItem(this));
        item->setName("16: 36-2-2-2 Crank only");
        model_->insert(item);
    }
    {
        QSharedPointer<TriggerPatternItem> item(new TriggerPatternItem(this));
        item->setName("17: 36-2-2-2 Crank and cam");
        model_->insert(item);
    }
    {
        QSharedPointer<TriggerPatternItem> item(new TriggerPatternItem(this));
        item->setName("18: GM 4200 crank wheel");
        model_->insert(item);
    }
    {
        QSharedPointer<TriggerPatternItem> item(new TriggerPatternItem(this));
        item->setName("19: Mazda FE3 36-1 with cam");
        model_->insert(item);
    }
    {
        QSharedPointer<TriggerPatternItem> item(new TriggerPatternItem(this));
        item->setName("20: Mitsubishi 6g72 with cam");
        model_->insert(item);
    }
    {
        QSharedPointer<TriggerPatternItem> item(new TriggerPatternItem(this));
        item->setName("21: Buell Oddfire CAM wheel");
        model_->insert(item);
    }
    {
        QSharedPointer<TriggerPatternItem> item(new TriggerPatternItem(this));
        item->setName("22: GM LS1 crank and cam");
        model_->insert(item);
    }
    {
        QSharedPointer<TriggerPatternItem> item(new TriggerPatternItem(this));
        item->setName("23: Odd Lotus 36-1-1-1-1 flywheel");
        model_->insert(item);
    }
    {
        QSharedPointer<TriggerPatternItem> item(new TriggerPatternItem(this));
        item->setName("24: Honda RC51 with cam");
        model_->insert(item);
    }
    {
        QSharedPointer<TriggerPatternItem> item(new TriggerPatternItem(this));
        item->setName("25: 36-1 crank with 2nd trigger on teeth 33-34");
        model_->insert(item);
    }
    {
        QSharedPointer<TriggerPatternItem> item(new TriggerPatternItem(this));
        item->setName("26: 36-1+1 crank with cam pattern NGC4");
        model_->insert(item);
    }
    {
        QSharedPointer<TriggerPatternItem> item(new TriggerPatternItem(this));
        item->setName("27: Weber-Marelli 8 crank+2 cam pattern");
        model_->insert(item);
    }
    {
        QSharedPointer<TriggerPatternItem> item(new TriggerPatternItem(this));
        item->setName("28: Fiat 1.8 16V crank and cam");
        model_->insert(item);
    }
    {
        QSharedPointer<TriggerPatternItem> item(new TriggerPatternItem(this));
        item->setName("29: Nissan 360 CAS with 6 slots");
        model_->insert(item);
    }
    {
        QSharedPointer<TriggerPatternItem> item(new TriggerPatternItem(this));
        item->setName("30: Mazda CAS 24-2 with single pulse outer ring");
        model_->insert(item);
    }
    {
        QSharedPointer<TriggerPatternItem> item(new TriggerPatternItem(this));
        item->setName("31: Yamaha 2002-03 R1 8 even-tooth crank with 1 tooth cam");
        model_->insert(item);
    }
    {
        QSharedPointer<TriggerPatternItem> item(new TriggerPatternItem(this));
        item->setName("32: GM 4 even-tooth crank with 1 tooth cam");
        model_->insert(item);
    }
    {
        QSharedPointer<TriggerPatternItem> item(new TriggerPatternItem(this));
        item->setName("33: GM 6 even-tooth crank with 1 tooth cam");
        model_->insert(item);
    }
    {
        QSharedPointer<TriggerPatternItem> item(new TriggerPatternItem(this));
        item->setName("34: GM 8 even-tooth crank with 1 tooth cam");
        model_->insert(item);
    }
    {
        QSharedPointer<TriggerPatternItem> item(new TriggerPatternItem(this));
        item->setName("35: Volvo d12[acd] crank with 7 tooth cam");
        model_->insert(item);
    }
    {
        QSharedPointer<TriggerPatternItem> item(new TriggerPatternItem(this));
        item->setName("36: Mazda 36-2-2-2 with 6 tooth cam");
        model_->insert(item);
    }
    {
        QSharedPointer<TriggerPatternItem> item(new TriggerPatternItem(this));
        item->setName("37: GM 60-2 with 4X cam");
        model_->insert(item);
    }
    {
        QSharedPointer<TriggerPatternItem> item(new TriggerPatternItem(this));
        item->setName("38: Dodge Viper Gen IV SRT V10 60-2 with 5 tooth cam");
        model_->insert(item);
    }
    {
        QSharedPointer<TriggerPatternItem> item(new TriggerPatternItem(this));
        item->setName("39: Suzuki GSX-1300R 24-1 crank and 1 tooth cam during missing crank tooth");
        model_->insert(item);
    }
    {
        QSharedPointer<TriggerPatternItem> item(new TriggerPatternItem(this));
        item->setName("40: Mitsubishi & Mazda 4g63 with cam");
        model_->insert(item);
    }
}
