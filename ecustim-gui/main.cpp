#include <QApplication>
#include <QQmlApplicationEngine>
#include <QLoggingCategory>
#include <QtQml/QQmlContext>
#include <QQmlEngine>
#include <QQuickStyle>
#include "Test.h"
#include "Communication/CommunicationManager.h"
#include "Communication/ProtocolHandler.h"
#include "Hardware/HardwareManager.h"


#if defined (Q_OS_ANDROID)
#include <QtAndroid>

////TODO: Looks like ACCESS_BACKGROUND_LOCATHardwareManagerN does not help, Location should be started manually
//const QVector<QString> permissions({"android.permission.ACCESS_BACKGROUND_LOCATHardwareManagerN",
//                                    "android.permission.ACCESS_FINE_LOCATHardwareManagerN",
//                                    "android.permission.ACCESS_COARSE_LOCATHardwareManagerN",
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

    //QSharedPointer<ProtocolHandler> protocolHandler(new ProtocolHandler);

    QSharedPointer<CommunicationManager> communicationManager(new CommunicationManager());

    QSharedPointer<HardwareManager> hardwareManager(new HardwareManager(communicationManager));

    Test test;
    //test.setProtocolHandler(protocolHandler);
    test.setCommunicator(communicationManager);
    test.setHardwareManager(hardwareManager);

#ifndef Q_OS_ANDROID
    test.show();
#endif

    QQuickStyle::setStyle("Material");

    QQmlApplicationEngine engine;
    engine.addImportPath("qrc:/qml");

    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl)
    {
        if (!obj && url == objUrl) QApplication::exit(-1);
    }
    , Qt::QueuedConnection);

    // To expose ENUM type from CommunicationManager QObject
    qmlRegisterUncreatableType<CommunicationManager>("CommunicationManager", 1, 0, "CommunicationManager", "");
    // To expose ENUM type from RemoteDeviceItem QObject
    qmlRegisterUncreatableType<RemoteDeviceItem>("RemoteDevice", 1, 0, "RemoteDevice", "");

    engine.rootContext()->setContextProperty("communicationManager", communicationManager.data());
    engine.rootContext()->setContextProperty("io", hardwareManager.data());
    engine.load(url);

    return app.exec();
}
