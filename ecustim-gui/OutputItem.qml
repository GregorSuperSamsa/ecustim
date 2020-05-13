import QtQuick 2.9
import QtQuick.Extras 1.4
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.3

Item {
    id: root
    //property int itemWidth: max()
    implicitHeight: 50
    implicitWidth: 100

    ColumnLayout
    {
        id: columnLayout
        anchors.fill: parent
        spacing: 0

        Switch
        {
            id: outputSwitch
            Layout.fillWidth: true
            Layout.preferredHeight: 30
            Layout.alignment: Qt.AlignCenter
            rotation: 270
        }

        Label
        {
            id: label
            Layout.fillWidth: true
            Layout.preferredHeight: contentHeight
            Layout.margins: 10
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            fontSizeMode: Text.VerticalFit
            //wrapMode: Text.WordWrap
            text: "Fuel pump relay"
        }
    }
}
