import QtQuick 2.12
import QtQuick.Extras 1.4
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.12
import QtQuick.Controls.Material 2.3
import '.'

Pane
{
    id: root
    //color: Material.background
    property string caption: ""
spacing: 0

padding: 4
    Material.background: Style.color.foreground

    Material.elevation: 10
    ColumnLayout
    {
        spacing: 0
        anchors.fill: parent

        Label
        {
            id: value

            Layout.fillWidth: true
            Layout.preferredHeight: contentHeight

            Layout.topMargin: 5
            Layout.bottomMargin: 5

            text: slider.value + "%"
            //fontSizeMode: Text.VerticalFit
            //Layout.fillHeight: false
            font.pixelSize: 16
            //font.pixelSize: Style.font.largePx * 2
            //color: Style.color.foreground
            //color: Style.color.background

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

        }


        RowLayout
        {
            Layout.fillHeight: true
            Layout.fillWidth: true

            Slider {
                Layout.fillHeight: true
                Layout.fillWidth: true

                id: slider
                from: 0
                to: 100
                stepSize: 1
                orientation: Qt.Vertical
                ToolTip.delay: 1500
                ToolTip.timeout: 3000
                ToolTip.visible: hovered && !pressed
                ToolTip.text: "Preset value"
                onValueChanged:
                    progress.value = slider.value

            }

            Slider {
                id: progress
                Layout.fillHeight: true
                Layout.fillWidth: true

                handle:Item{}
                from: slider.from
                to: slider.to
                stepSize: slider.stepSize
                orientation: Qt.Vertical
                ToolTip.delay: 1500
                ToolTip.timeout: 3000
                ToolTip.visible: hovered && !pressed
                ToolTip.text: "Actual value"
            }
        }

        Label
        {
            id: type
            Layout.fillWidth: true
            Layout.preferredHeight: contentHeight
            //Layout.topMargin: 5

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            text: caption
            //fontSizeMode: Text.VerticalFit
        }
    }
}
