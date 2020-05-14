import QtQuick 2.6
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0
import QtQuick.Controls.Material 2.3


Item
{
    GroupBox
    {
        id: control
        title: "Variable Outputs"
        background: Rectangle{anchors.fill: parent; color: "transparent"}
        anchors.fill: parent

        RowLayout
        {
            anchors.margins:  -12
            anchors.fill: parent
            clip:true
            spacing: 5
            VariableOutputItem
            {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignCenter
                caption: "RPM"
            }

            VariableOutputItem
            {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignCenter
                caption: "MAP"
            }
            VariableOutputItem
            {
                Layout.fillWidth: true
                Layout.fillHeight: true
                // Layout.preferredWidth: 100
                Layout.alignment: Qt.AlignCenter
                caption: "TPS"
            }
            VariableOutputItem
            {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignCenter
                caption: "IAT"
            }
            VariableOutputItem
            {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignCenter
                caption: "CLT"
            }
            VariableOutputItem
            {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignCenter
                caption: "O2"
            }
        }
    }
}
