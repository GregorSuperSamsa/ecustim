import QtQuick 2.6
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.12
import QtQuick.Controls.Material 2.3
import QtQml.Models 2.2
import RemoteDevice 1.0


DelegateModel {

    property int selectedIndex: -1
    property color selectedBackground:  Material.color(Material.Grey, Material.Shade700)
    property color idleBackground:      "#404040"

    // Data model
    model: communicationManager.remoteDeviceModel

    // Delegate component
    delegate: Pane {
        property bool  expanded: false
        property bool  selected: selectedIndex == index
//radius: 2
        id: pane
        implicitHeight: columnLayout.implicitHeight + topPadding + bottomPadding
        implicitWidth: parent.width
       Material.background:  selected ? selectedBackground : idleBackground
       Material.elevation: 1

        //        MouseArea {
        //            parent: pane
        //            width: parent.width
        //            height: parent.height
        //            propagateComposedEvents: true
        //            onClicked:
        //                if (buttonMoreMouseArea.containsMouse)
        //                    mouse.accepted = false
        //                else if (buttonConnectMouseArea.containsMouse)
        //                {
        //                    mouse.accept = false
        //                }
        //                else
        //                {
        //                    selectedIndex = index
        //                    connectionString = item.connectionString
        //                }
        //        }

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
                    text: item.displayText
                }

                RoundButton {
                    id: buttonConnectDisconnect

                    Layout.margins: -10
                    Layout.fillHeight: true
                    Layout.preferredWidth: height

                    flat: true
                    radius: 2

                    icon.source: item.connectionState === RemoteDevice.CONNECTED ? "qrc:/images/link-black-24dp.svg" : "qrc:/images/link_off-black-24dp.svg"
                    icon.color:  item.connectionState === RemoteDevice.CONNECTED ? Material.accent : Material.foreground

                    Connections {
                        target: item
                        onConnectionStateChanged: {
                            iconAnimation.stop();
                            buttonConnectDisconnect.opacity = 1
                        }
                    }

                    SequentialAnimation {
                        id: iconAnimation
                        running: false
                        loops: -1
                        //alwaysRunToEnd: true
                        NumberAnimation {
                            target: buttonConnectDisconnect
                            property: "opacity"
                            duration: 700
                            from: 1
                            to: 0
                        }
                        NumberAnimation {
                            target: buttonConnectDisconnect
                            property: "opacity"
                            duration: 700
                            from: 0
                            to: 1
                        }
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            iconAnimation.start();
                            if (item.connectionState === RemoteDevice.CONNECTED) {
                                communicationManager.disconnect();
                            }
                            else {
                                communicationManager.connect(item.connectionString);
                            }
                        }
                    }
                }

                RoundButton {
                    id: buttonMore
                    Layout.margins: -10
                    Layout.fillHeight: true
                    Layout.preferredWidth: height
                    flat: true
                    icon.source: expanded ?  "qrc:/images/expand_less-black-24dp.svg" : "qrc:/images/expand_more-black-24dp.svg"
                    radius: 2
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
                Repeater {
                    model: item.additionalInfo
                    Label {
                        Layout.preferredWidth: contentWidth
                        Layout.preferredHeight: contentHeight
                        elide: Text.ElideRight
                        text: modelData
                    }
                }
            }
        }
    }
}
