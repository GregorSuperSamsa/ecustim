import QtQuick 2.9
import QtQuick.Extras 1.4
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.3

Item {
    id: root
    implicitHeight: columnLayout.implicitHeight
    implicitWidth: columnLayout.implicitWidth

    property string caption: ""

    ColumnLayout
    {
        id: columnLayout
        anchors.fill: parent
        spacing: 0

        Switch
        {
            id: outputSwitch
            Layout.preferredWidth: 30
            Layout.preferredHeight: 30
            Layout.alignment: Qt.AlignCenter
            rotation: 270
        }

        Label
        {
            id: label
            Layout.fillWidth: true
            Layout.preferredHeight: contentHeight
            Layout.topMargin: 5

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            fontSizeMode: Text.VerticalFit

            text: caption
        }
    }
}
