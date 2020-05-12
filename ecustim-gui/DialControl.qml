import QtQuick 2.12
import QtQuick.Controls 2.5
//import QtQuick.Extras 1.4
import QtQuick.Controls.Styles 1.4

import '.'


Item {

    signal dialValueChanged(int value)

    property int currentValue: 0
    property int minValue: 0
    property int maxValue: 0
    property color colorBackground: "white";
    property color colorActive: "white";
    property color colorIdle: "white";
    property int drawWidth: 3


    //property color background: value

    id: root


    Dial
    {
        id: dial
        anchors.fill: parent
        from: minValue
        to: maxValue
        stepSize: 1
        snapMode: Dial.SnapAlways

        background: Rectangle {
            x: dial.width / 2 - width / 2
            y: dial.height / 2 - height / 2
            width: Math.max(64, Math.min(dial.width, dial.height))
            height: width
            color: colorBackground
            radius: width / 2
            border.width: drawWidth
            border.color: dial.pressed ? colorActive : colorIdle
            opacity: dial.enabled ? 1 : 0.3
        }

        handle: Rectangle
        {
            id: handleItem
            x: dial.background.x + dial.background.width / 2 - width / 2
            y: dial.background.y + dial.background.height / 2 - height / 2
            width: 16
            height: 16
            color: dial.pressed ? colorActive : colorIdle
            radius: 8
            //antialiasing: true
            opacity: dial.enabled ? 1 : 0.3
            transform: [
                Translate {
                    y: -Math.min(dial.background.width, dial.background.height) * 0.4 + handleItem.height / 2
                },
                Rotation {
                    angle: dial.angle
                    origin.x: handleItem.width / 2
                    origin.y: handleItem.height / 2
                }
            ]
        }
        onValueChanged:
        {
            currentValue = value
            dialValueChanged(currentValue);
        }
    }
}
