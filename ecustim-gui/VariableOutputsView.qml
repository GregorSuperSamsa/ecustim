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
        background: Item{}
        anchors.fill: parent

        RowLayout
        {
            anchors.margins:  -12
            anchors.fill: parent
            clip:true
            spacing: 5
            SensorItem2
            {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignCenter
                caption: "RPM"
            }

            SensorItem2
            {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignCenter
                caption: "MAP"
            }
            SensorItem2
            {
                Layout.fillWidth: true
                Layout.fillHeight: true
                // Layout.preferredWidth: 100
                Layout.alignment: Qt.AlignCenter
                caption: "TPS"
            }
            SensorItem2
            {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignCenter
                caption: "IAT"
            }
            SensorItem2
            {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignCenter
                caption: "CLT"
            }
            SensorItem2
            {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignCenter
                caption: "O2"
            }
        }
    }
}
