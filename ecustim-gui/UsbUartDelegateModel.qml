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
    model: communicator.serialModel

    // Delegate component
    delegate: Pane {
        property bool  expanded: false
        property bool  selected: selectedIndex == index

        id: pane
        implicitHeight: columnLayout.implicitHeight + topPadding + bottomPadding
        implicitWidth: parent.width
        Material.background: selected ? selectedBackground : idleBackground
        Material.elevation: 10

        MouseArea {
            parent: pane
            width: parent.width
            height: parent.height
            propagateComposedEvents: true
            onClicked:
                if (buttonMoreMouseArea.containsMouse)
                    mouse.accepted = false
                else
                    selectedIndex = index
        }

        ColumnLayout {
            id: columnLayout
            anchors.fill: parent

            RowLayout {
                Layout.fillWidth: true
                Layout.preferredHeight: implicitHeight

                // Device name
                Label {
                    id: labelName
                    Layout.fillWidth: true
                    Layout.preferredHeight: contentHeight
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                    text: item.name
                }

                RoundButton {
                    id: buttonMore
                    Layout.margins: -10
                    Layout.preferredHeight: 40
                    Layout.preferredWidth: 40
                    // Tooltip
                    ToolTip.delay: 1500
                    ToolTip.timeout: 3000
                    ToolTip.visible: hovered
                    ToolTip.text: "Additional information"
                    flat: true
                    text: "..."

                    MouseArea {
                        id:  buttonMoreMouseArea
                        anchors.fill: parent
                        hoverEnabled: true
                        onClicked: expanded = !expanded
                    }
                }
            }

            GridLayout {
                id: grid
                Layout.fillWidth: true
                Layout.fillHeight: true
                columns: 2
                visible: expanded

                // Location on the Bus
                Label {
                    Layout.preferredWidth: contentWidth
                    Layout.preferredHeight: contentHeight
                    elide: Text.ElideRight
                    text: "Location:"
                }
                Label {
                    Layout.preferredWidth: contentWidth
                    Layout.preferredHeight: contentHeight
                    elide: Text.ElideRight
                    text: item.location
                }
                // Description
                Label {
                    Layout.preferredWidth: contentWidth
                    Layout.preferredHeight: contentHeight
                    elide: Text.ElideRight
                    text: "Description:"
                }
                Label {
                    Layout.preferredWidth: contentWidth
                    Layout.preferredHeight: contentHeight
                    elide: Text.ElideRight
                    text: item.description
                }
                // Manufacturer
                Label {
                    Layout.preferredWidth: contentWidth
                    Layout.preferredHeight: contentHeight
                    elide: Text.ElideRight
                    text: "Manufacturer:"
                }
                Label {
                    Layout.preferredWidth: contentWidth
                    Layout.preferredHeight: contentHeight
                    elide: Text.ElideRight
                    text: item.manufacturer
                }
                // Serial number
                Label {
                    Layout.preferredWidth: contentWidth
                    Layout.preferredHeight: contentHeight
                    elide: Text.ElideRight
                    text: "Serial number:"
                }
                Label {
                    Layout.preferredWidth: contentWidth
                    Layout.preferredHeight: contentHeight
                    elide: Text.ElideRight
                    text: item.serialNumber
                }
                // Vendor Id
                Label {
                    Layout.preferredWidth: contentWidth
                    Layout.preferredHeight: contentHeight
                    elide: Text.ElideRight
                    text: "Vendor Id:"
                }
                Label {
                    Layout.preferredWidth: contentWidth
                    Layout.preferredHeight: contentHeight
                    elide: Text.ElideRight
                    text: item.vendorId
                }
                // Product Id
                Label {
                    Layout.preferredWidth: contentWidth
                    Layout.preferredHeight: contentHeight
                    elide: Text.ElideRight
                    text: "Product Id:"
                }
                Label {
                    Layout.preferredWidth: contentWidth
                    Layout.preferredHeight: contentHeight
                    elide: Text.ElideRight
                    text: item.productId
                }
            }
        }
    }
}
