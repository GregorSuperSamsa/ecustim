import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

Item
{
    id: root

    property string caption: ""
    property real setValue: 0
    property real actualValue: 0

    implicitHeight: columnLayout.implicitHeight
    implicitWidth: columnLayout.implicitWidth

    ColumnLayout {
        id: columnLayout
        anchors.fill: parent
        spacing: 0

        Switch {
            id: outputSwitch

            Layout.preferredHeight: implicitWidth
            Layout.alignment: Qt.AlignHCenter

            rotation: 270
            implicitWidth: 60
            implicitHeight: 30
        }

        Label {
            id: label
            Layout.alignment: Qt.AlignHCenter
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            text: caption
        }
    }
}
