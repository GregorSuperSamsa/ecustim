QT += quick serialport bluetooth widgets charts quickcontrols2

CONFIG += c++11

TARGET = ecustim-gui

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
#DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Communication/Communication.cpp \
    Communication/CommunicationManager.cpp \
    Communication/Bluetooth/Bluetooth.cpp \
    Communication/RemoteDeviceItem.cpp \
    Communication/Uart/Uart.cpp \
    Hardware/IO/IOItem.cpp \
    Hardware/IO/IOManager.cpp \
    Hardware/TriggerGenerator.cpp \
    UI/Model.cpp \
    Test.cpp \
    main.cpp

HEADERS += \
    Communication/Communication.h \
    Communication/CommunicationManager.h \
    Communication/Bluetooth/Bluetooth.h \
    Communication/RemoteDeviceItem.h \
    Communication/Uart/Uart.h \
    Hardware/IO/IOItem.h \
    Hardware/IO/IOManager.h \
    Hardware/TriggerGenerator.h \
    UI/Model.h \
    Test.h

FORMS += \
    Test.ui

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
#QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
#QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


if (contains(ANDROID_TARGET_ARCH, arm64-v8a) || contains(ANDROID_TARGET_ARCH, armeabi-v7a)) {

QT+= androidextras

ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}

#QMAKE_POST_LINK = sudo setcap CAP_NET_ADMIN=eip $TARGET

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml
