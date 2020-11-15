import QtQuick 2.12
import QtQuick.Extras 1.4
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.12
import QtQuick.Controls.Material 2.3
import '.'

Item
{
    id: root
    implicitHeight: 150

    property string caption: ""
    property real setValue: 0
    property string valueUnits: "\u03A9"
    property real actualValue: 0
    property real i2cAddress: 0xFF

    ColumnLayout
    {
        anchors.fill: parent
        spacing: 0
        // Set output value placeholder
        Item
        {
            Layout.fillWidth: true
            Layout.preferredHeight: labelValue.height
            //Layout.topMargin: 5
            Layout.bottomMargin: 3
            // Set output value reading
            Label
            {
                id: labelValue
                anchors.centerIn: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                text: sliderSetValue.value.toFixed(0)
                // 20% bigger than default font
                font.pointSize: labelValueUnit.font.pointSize * 1.2
            }
            // Set output value unit
            Label
            {
                id: labelValueUnit
                anchors.left: labelValue.right
                anchors.bottom: labelValue.bottom
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                text: " " + valueUnits
            }
        }
        // Set output value slider placeholder
        RowLayout
        {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 0

            Slider {
                id: sliderSetValue
                Layout.fillHeight: true
                Layout.fillWidth: true

                from: 0
                to: 111
                stepSize: 1
                orientation: Qt.Vertical
                onValueChanged: setValue = value
            }

            //            Slider
            //            {
            //                id: sliderReadValue
            //                enabled: false
            //                Layout.fillHeight: true
            //                Layout.fillWidth: true

            //                handle:Item{}
            //                from: sliderSetValue.from
            //                to: sliderSetValue.to
            //                stepSize: sliderSetValue.stepSize
            //                orientation: Qt.Vertical
            //                ToolTip.delay: 1500
            //                ToolTip.timeout: 3000
            //                ToolTip.visible: hovered && !pressed
            //                ToolTip.text: "Actual value"
            //                value: actualValue
            //            }

        }
        // Caption (name) of the output value
        Label
        {
            id: labelCaption
            Layout.fillWidth: true
            Layout.preferredHeight: implicitHeight
            Layout.topMargin: 5
            Layout.bottomMargin: 5

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            text: caption
        }
    }
}
