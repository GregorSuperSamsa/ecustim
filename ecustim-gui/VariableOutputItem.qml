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
    property string caption: ""
    implicitHeight: pane.implicitHeight

    Pane
    {
        id: pane
        anchors.fill: parent
        padding: 4
        implicitHeight: 100
        Material.background: Style.color.foreground
        Material.elevation: 10

        ColumnLayout
        {
            anchors.fill: parent
            spacing: 0

            Label
            {
                id: value

                Layout.fillWidth: true
                Layout.preferredHeight: contentHeight
                Layout.topMargin: 5
                Layout.bottomMargin: 5

                text: slider.value + "%"
                font.pixelSize: 16

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            RowLayout
            {
                Layout.fillHeight: true
                Layout.fillWidth: true

                Slider
                {
                    id: slider
                    Layout.fillHeight: true
                    Layout.fillWidth: true

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

                Slider
                {
                    id: progress
                    enabled: false
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
                Layout.topMargin: 5
                Layout.bottomMargin: 5

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                text: caption
            }
        }
    }
}
