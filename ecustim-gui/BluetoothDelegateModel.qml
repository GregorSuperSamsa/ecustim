import QtQuick 2.6
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.12
import QtQuick.Controls.Material 2.3
import QtQml.Models 2.2
import '.'


DelegateModel
{
    property int selectedIndex: -1
    property color selectedBackground:  Material.color(Material.Grey, Material.Shade700)
    property color idleBackground:      Style.color.foreground

    // Data model
    model: communicator.bluetoothModel

    // Delegate component
    delegate: Pane {
        property bool  selected: selectedIndex == index

        id: pane
        implicitHeight: rowLayout.implicitHeight + topPadding + bottomPadding
        implicitWidth: parent.width
        Material.background: selected ? selectedBackground : idleBackground
        Material.elevation: 10

        MouseArea {
            parent: pane
            width: parent.width
            height: parent.height
            onClicked:
                selectedIndex = index
        }

        RowLayout {
            id: rowLayout
            anchors.fill: parent
            // Device address
            Label {
                id: labelAddress
                Layout.fillWidth: true
                Layout.preferredHeight: contentHeight
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
                text: item.address
            }
            // Device name
            Label {
                id: labelName
                Layout.fillWidth: true
                Layout.preferredHeight: contentHeight
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
                text: item.name
            }
            // RSSI
            Label {
                id: labelRSSI
                Layout.fillWidth: true
                Layout.preferredHeight: contentHeight
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
                text: item.RSSI
            }
        }
    }
}
