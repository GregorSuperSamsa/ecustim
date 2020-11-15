win32 {
    HOMEDIR += $$(USERPROFILE)
}
else {
    HOMEDIR += $$(HOME)
}

INCLUDEPATH += "$${HOMEDIR}/git/ecustim/ecustim-firmware/include"
INCLUDEPATH += "$${HOMEDIR}/git/ecustim/ecustim-firmware/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduino-avr/cores/arduino"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduino-avr/variants/mega"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduino-avr/libraries/EEPROM/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduino-avr/libraries/HID/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduino-avr/libraries/SPI/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduino-avr/libraries/SoftwareSerial/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/framework-arduino-avr/libraries/Wire/src"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/toolchain-atmelavr/lib/gcc/avr/5.4.0/include-fixed"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/toolchain-atmelavr/lib/gcc/avr/5.4.0/include"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/toolchain-atmelavr/avr/include"
INCLUDEPATH += "$${HOMEDIR}/.platformio/packages/tool-unity"

DEFINES += "PLATFORMIO=50000"
DEFINES += "ARDUINO_AVR_MEGA2560"
DEFINES += "F_CPU=16000000L"
DEFINES += "ARDUINO_ARCH_AVR"
DEFINES += "ARDUINO=10808"
DEFINES += "__AVR_ATmega2560__"

OTHER_FILES += platformio.ini

