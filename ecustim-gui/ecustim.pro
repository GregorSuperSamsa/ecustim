QT += quick serialport bluetooth widgets charts quickcontrols2 svg

TARGET = ecustim-gui

VERSHardwareManagerN = 0.2

CONFIG += c++17

SOURCES += \
    Communication/Communication.cpp \
    Communication/CommunicationManager.cpp \
    Communication/Bluetooth.cpp \
    #Communication/ProtocolHandler.cpp \
    Communication/RemoteDeviceItem.cpp \
    Communication/Uart.cpp \
    Hardware/IOItem.cpp \
    Hardware/HardwareManager.cpp \
    Hardware/HardwareItem.cpp \
    Hardware/TriggerPatternItem.cpp \
    UI/Model.cpp \
    Test.cpp \
    main.cpp

HEADERS += \
    Communication/Communication.h \
    Communication/CommunicationManager.h \
    Communication/Bluetooth.h \
    Communication/Protocol.h \
    #Communication/ProtocolHandler.h \
    Communication/RemoteDeviceItem.h \
    Communication/Uart.h \
    Hardware/IOItem.h \
    Hardware/HardwareManager.h \
    Hardware/HardwareItem.h \
    Hardware/TriggerPatternItem.h \
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
