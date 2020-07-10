#include <QApplication>
#include <QQmlApplicationEngine>
#include <QLoggingCategory>
#include <QtQml/QQmlContext>
#include <QQmlEngine>
#include <QQuickStyle>
#include "Test.h"
#include "Communication/CommunicationManager.h"
#include "Hardware/TriggerGenerator.h"
#include "Hardware/IO/IOManager.h"


#if defined (Q_OS_ANDROID)
#include <QtAndroid>

////TODO: Looks like ACCESS_BACKGROUND_LOCATION does not help, Location should be started manually
//const QVector<QString> permissions({"android.permission.ACCESS_BACKGROUND_LOCATION",
//                                    "android.permission.ACCESS_FINE_LOCATION",
//                                    "android.permission.ACCESS_COARSE_LOCATION",
//                                    "android.permission.BLUETOOTH",
//                                    "android.permission.BLUETOOTH_ADMIN",
//                                    "android.permission.WRITE_EXTERNAL_STORAGE",
//                                    "android.permission.READ_EXTERNAL_STORAGE"});
#endif


int main(int argc, char *argv[])
{

    //QLoggingCategory::setFilterRules(QStringLiteral("qt.bluetooth* = true"));
//#if defined (Q_OS_ANDROID)
//    QLoggingCategory::setFilterRules(QStringLiteral("qt.bluetooth* = true"));
//#endif

    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

//#if defined (Q_OS_ANDROID)
//    //Request requiered permissions at runtime
//    for(const QString &permission : permissions){
//        auto result = QtAndroid::checkPermission(permission);
//        if(result == QtAndroid::PermissionResult::Denied){
//            auto resultHash = QtAndroid::requestPermissionsSync(QStringList({permission}));
//            if(resultHash[permission] == QtAndroid::PermissionResult::Denied)
//                return 0;
//        }
//    }
//#endif


    QSharedPointer<CommunicationManager> communicationManager(new CommunicationManager);

    TriggerGenerator tg(communicationManager);

    QSharedPointer<IO> io( new IO(communicationManager));

    Test test;
    test.setCommunicator(communicationManager);
    test.setIO(io);

#ifndef Q_OS_ANDROID
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

    // In order to expose ENUM type from CommunicationManager QObject
    qmlRegisterUncreatableType<CommunicationManager>("CommunicationManager", 1, 0, "CommunicationManager", "");
    //
    engine.rootContext()->setContextProperty("communicationManager", communicationManager.data());
    engine.rootContext()->setContextProperty("io", io.data());
    engine.rootContext()->setContextProperty("testis", &tg);
    engine.load(url);

    return app.exec();
}
