import QtQuick 2.12
import QtQuick.Extras 1.4
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.12


Item
{
    id: root

    property string caption: ""
    property alias dial: dial
    width: 150
    height: 250

    Rectangle
    {
        anchors.fill: parent
        border.width: 2
        border.color: Style.color.foreground
        color: Style.color.background
        //color: Style.color.foreground
        radius: 5

        ColumnLayout
        {
            spacing: 0
            anchors.fill: parent

            Label
            {
                background: Rectangle
                {
               radius: 5
                    anchors.fill: parent
                    border.color: Style.color.foreground
                    color: Style.color.background
                    border.width: 2

                }

                id: value
                //Layout.alignment:  Qt.AlignTop
                Layout.fillWidth: true
                Layout.preferredHeight: contentHeight
                Layout.margins: 20
                text: dial.currentValue + "%"
                font.pixelSize: Style.font.largePx * 2
                color: Style.color.foreground
                //color: Style.color.background

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

            }

            DialControl
            {
                id: dial
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.margins: 10

                minValue: 0
                maxValue: 100
                drawWidth: 3
                colorBackground: Style.color.background
                colorActive: "black"
                colorIdle: Style.color.foreground

//                colorBackground: Style.color.foreground
//                colorActive: "white"
//                colorIdle: Style.color.background

                onDialValueChanged:
                    console.log("Dial" + value)

            }

            Label
            {
                Layout.fillWidth: true
                Layout.preferredHeight: contentHeight
                Layout.alignment: Qt.AlignBottom
                Layout.margins: 10

                id: type
                text: caption
                font.pixelSize: Style.font.largePx
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                color: Style.color.foreground
            }
        }
    }
}















//}















//    CircularGauge
//    {
//        anchors.top: parent.top
//        anchors.horizontalCenter: parent.horizontalCenter
//        width: sensor_control.width * 0.9
//        height: sensor_control.width * 0.9
//        id: gauge
//        minimumValue: minValue
//        maximumValue: maxValue
//        style: CircularGaugeStyle
//        {
//            //
//            foreground: Rectangle
//            {
//                color: "transparent"
//            }
//            //
//            needle: Rectangle
//            {
//                Image
//                {
//                    height: gauge.height * 0.8
//                    fillMode: Image.PreserveAspectFit
//                    anchors.centerIn: parent
//                    id: name
//                    clip: true
//                    source: "file:/gauge-needle-png.png"
//                    antialiasing: true
//                    visible: true
//                }
//            }
//        }

//        Behavior on value {
//            NumberAnimation {
//                duration:  700
//            }
//        }
//    }
