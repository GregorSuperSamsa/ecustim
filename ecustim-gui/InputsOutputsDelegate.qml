import QtQuick 2.6
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.12
import QtQuick.Controls.Material 2.3
import QtQml.Models 2.2
import QtGraphicalEffects 1.0
import RemoteDevice 1.0
//import '.'


//Item {

//    property string caption: "pederast"
//    property int selectedIndex: -1
//    property color selectedBackground:  Material.color(Material.Grey, Material.Shade700)
//    property color idleBackground:      Style.color.foreground
//    property bool  expanded: false
//    property bool  selected: false

//    // Data model
//    //model: io.voModel

//    // Delegate component
//    //delegate:
Pane {

    property string caption: ""
    property int selectedIndex: -1
    property color selectedBackground:  Material.color(Material.Grey, Material.Shade700)
    property color idleBackground:      Style.color.foreground
    property bool  expanded: false
    property bool  selected: false

    onCaptionChanged:
    {
        console.log("caption changed")
    }


    id: pane
            //implicitHeight: columnLayout.implicitHeight + topPadding + bottomPadding
            //implicitWidth: parent.width
    Material.background: selected ? selectedBackground : idleBackground
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
            //Layout.preferredWidth: implicitWidth
            Layout.preferredHeight: implicitHeight

            // Device name
            Label {
                id: labelName
                Layout.preferredWidth: implicitContentWidth
                Layout.fillHeight: true
                //Layout.preferredHeight: contentHeight
                //verticalAlignment: Text.AlignVCenter
                //elide: Text.ElideRight
                text: caption
            }

            RoundButton {
                id: buttonDelete
                Layout.alignment: Qt.AlignRight
                Layout.margins: -10
                Layout.fillHeight: true
                Layout.preferredWidth: height

                flat: true
                radius: 4

                icon.source: "qrc:/clear-black-24dp.svg"
                //icon.color:  item.connectionState === RemoteDevice.CONNECTED ? Material.accent : Material.foreground

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        //
                    }
                }
            }

            //                RoundButton {
            //                    id: buttonMore
            //                    Layout.margins: -10
            //                    Layout.fillHeight: true
            //                    Layout.preferredWidth: height
            //                    flat: true
            //                    icon.source: expanded ?  "qrc:/expand_less-black-24dp.svg" : "qrc:/expand_more-black-24dp.svg"
            //                    radius: 4
            //                    MouseArea {
            //                        id:  buttonMoreMouseArea
            //                        anchors.fill: parent
            //                        hoverEnabled: true
            //                        onClicked: expanded = !expanded
            //                    }
            //                }
        }

        GridLayout {
            id: grid
            Layout.fillWidth: true
            Layout.fillHeight: true
            columns: 2
            visible: expanded
            //                Repeater {
            //                    model: item.additionalInfo
            //                    Label {
            //                        Layout.preferredWidth: contentWidth
            //                        Layout.preferredHeight: contentHeight
            //                        elide: Text.ElideRight
            //                        text: modelData
            //                    }
            //                }
        }
    }
}
//}
