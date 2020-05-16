#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml/QQmlContext>
#include <QQuickStyle>
#include "Test.h"
#include "Communicator.h"
#include "TriggerGenerator.h"


int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    QSharedPointer<Communicator> communicator(new Communicator);
    communicator->Ports();

    TriggerGenerator tg(communicator);


#ifndef Q_OS_ANDROID
    Test test;
    test.show();
#endif


    QQuickStyle::setStyle("Material");
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl)
    {
        if (!obj && url == objUrl) QApplication::exit(-1);
    }
    , Qt::QueuedConnection);


    engine.rootContext()->setContextProperty("testis", &tg);
    engine.load(url);


    return app.exec();
}
