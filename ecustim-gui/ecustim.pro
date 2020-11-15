QT += quick serialport bluetooth widgets charts quickcontrols2 svg

TARGET = ecustim-gui

VERSION = 0.1

CONFIG += c++17

SOURCES += \
    Communication/Communication.cpp \
    Communication/CommunicationManager.cpp \
    Communication/Bluetooth/Bluetooth.cpp \
    Communication/RemoteDeviceItem.cpp \
    Communication/Uart/Uart.cpp \
    Hardware/IO/IOItem.cpp \
    Hardware/IO/IOManager.cpp \
    Hardware/TriggerPattern/TriggerPatternItem.cpp \
    Hardware/TriggerPattern/TriggerPatternManager.cpp \
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
    Hardware/TriggerPattern/TriggerPatternItem.h \
    Hardware/TriggerPattern/TriggerPatternManager.h \
    UI/Model.h \
    Test.h

FORMS += \
    Test.ui

RESOURCES += qml.qrc \
    resources.qrc

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
