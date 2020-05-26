import QtQuick 2.6
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0
import QtQuick.Controls.Material 2.3


Item
{
    id: root
    ColumnLayout
    {
        anchors.fill: parent
        anchors.leftMargin: 10
        anchors.rightMargin: 10

        RowLayout
        {
            id: rowLayout
            Layout.alignment: Qt.AlignTop
            Layout.fillWidth: true
            Layout.preferredHeight: contentItem.implicitHeight
            spacing: 9

            RadioButton
            {
                id: radioButtonBluetooth
                Layout.fillWidth: true
                Layout.preferredWidth: 1
                Layout.preferredHeight: implicitHeight
                text: qsTr("Bluetooth")
            }

            RadioButton
            {
                id: radioButtonUsbUart
                Layout.fillWidth: true
                Layout.preferredWidth: 1
                Layout.preferredHeight: implicitHeight
                text: qsTr("USB UART")
            }

            Item
            {
                Layout.fillWidth: true
                Layout.preferredWidth: 2
            }
        }

        ListView
        {

            id: list
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 10

            clip:true
            flickableDirection: Flickable.VerticalFlick
            boundsBehavior: Flickable.StopAtBounds
            ScrollBar.vertical: ScrollBar {id: scrollbar}

            model: radioButtonUsbUart.checked ? communicator.serialModel : communicator.bluetoothModel
            delegate: delegate
        }

        RowLayout
        {
            Layout.alignment: Qt.AlignHCenter | Qt.AlignBottom
            Layout.fillWidth: true
            Layout.preferredHeight: contentItem.implicitHeight

            Button
            {
                id: buttonRefresh
                Layout.fillWidth: true
                Layout.preferredHeight: implicitHeight
                text: "Refresh"
            }

            Button
            {
                Layout.fillWidth: true
                Layout.preferredHeight: implicitHeight
                id: buttonConnect
                text: "Connect"
            }
        }
    }


    // Delegate
    Component
    {
        id: delegate

        Pane
        {
            id: pane

            property bool selected: index == list.currentIndex
            property bool expanded: false

            implicitHeight: columnLayout.implicitHeight + topPadding + bottomPadding
            implicitWidth: parent.width
            Material.background: selected ? Material.color(Material.Grey, Material.Shade700) : Style.color.foreground
            Material.elevation: 10

            MouseArea
            {
                parent: pane
                width: parent.width
                height: parent.height
                propagateComposedEvents: true
                onClicked:
                    if (buttonMoreMouseArea.containsMouse)
                        mouse.accepted = false
                    else
                        list.currentIndex = index
            }

            ColumnLayout
            {
                id: columnLayout
                anchors.fill: parent

                RowLayout
                {
                    Layout.fillWidth: true
                    Layout.preferredHeight: implicitHeight

                    Label
                    {
                        id: nameData
                        Layout.fillWidth: true
                        Layout.preferredHeight: contentHeight
                        verticalAlignment: Text.AlignVCenter
                        elide: Text.ElideRight
                        text: item.name
                    }

                    RoundButton
                    {
                        id: buttonMore
                        flat: true
                        Layout.margins: -10
                        Layout.preferredHeight: 40
                        Layout.preferredWidth: 40
                        text: "..."
                        ToolTip.delay: 1500
                        ToolTip.timeout: 3000
                        ToolTip.visible: hovered
                        ToolTip.text: "Additional information"

                        MouseArea
                        {
                            id:  buttonMoreMouseArea
                            anchors.fill: parent
                            hoverEnabled: true
                            onClicked:
                                expanded = !expanded
                        }
                    }
                }

                GridLayout
                {
                    id: grid
                    columns: 2
                    visible: expanded
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    Label {
                        id: location
                        Layout.preferredWidth: contentWidth
                        Layout.preferredHeight: contentHeight
                        elide: Text.ElideRight
                        text: "Location:"
                    }
                    Label {
                        id: locationData
                        Layout.preferredWidth: contentWidth
                        Layout.preferredHeight: contentHeight
                        elide: Text.ElideRight
                        text: item.location
                    }
                    //
                    Label {
                        id: description
                        Layout.preferredWidth: contentWidth
                        Layout.preferredHeight: contentHeight
                        elide: Text.ElideRight
                        text: "Description:"
                    }
                    Label {
                        id: descriptionData
                        Layout.preferredWidth: contentWidth
                        Layout.preferredHeight: contentHeight
                        elide: Text.ElideRight
                        text: item.description
                    }
                    //
                    Label {
                        id: manufacturer
                        Layout.preferredWidth: contentWidth
                        Layout.preferredHeight: contentHeight
                        elide: Text.ElideRight
                        text: "Manufacturer:"
                    }
                    Label {
                        id: manufacturerData
                        Layout.preferredWidth: contentWidth
                        Layout.preferredHeight: contentHeight
                        elide: Text.ElideRight
                        text: item.manufacturer
                    }
                    //
                    Label {
                        id: serialNumber
                        Layout.preferredWidth: contentWidth
                        Layout.preferredHeight: contentHeight
                        elide: Text.ElideRight
                        text: "Serial number:"
                    }
                    Label {
                        id: serialNumberData
                        Layout.preferredWidth: contentWidth
                        Layout.preferredHeight: contentHeight
                        elide: Text.ElideRight
                        text: item.serialNumber
                    }
                    //
                    Label {
                        id: vendorId
                        Layout.preferredWidth: contentWidth
                        Layout.preferredHeight: contentHeight
                        elide: Text.ElideRight
                        text: "Vendor Id:"
                    }
                    Label {
                        id: vendorIdData
                        Layout.preferredWidth: contentWidth
                        Layout.preferredHeight: contentHeight
                        elide: Text.ElideRight
                        text: item.vendorId
                    }
                    //
                    Label {
                        id: productId
                        Layout.preferredWidth: contentWidth
                        Layout.preferredHeight: contentHeight
                        elide: Text.ElideRight
                        text: "Product Id:"
                    }
                    Label {
                        id: productIdData
                        Layout.preferredWidth: contentWidth
                        Layout.preferredHeight: contentHeight
                        elide: Text.ElideRight
                        text: item.productId
                    }
                }
            }
        }
    }
}

