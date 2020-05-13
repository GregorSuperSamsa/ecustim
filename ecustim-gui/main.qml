import QtQuick 2.6
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0
import QtQuick.Controls.Material 2.3

ApplicationWindow
{
    Material.theme: Material.Dark
    Material.accent: Material.DeepOrange

    id: root
    visible: true
    width: 600
    height: 480
    title: qsTr("Ecustim")
    //color: Style.color.background

    ListModel
    {
        id: menuModel
        ListElement { title: "Trigger pattern"; index: 0; iconSource: "file:/trigger-wheel-1.png"}
        ListElement { title: "Sensors"; index: 1; iconSource: "file:/rpm.png" }
        //ListElement { title: "Inputs"; index: 2; iconSource: "file:/input.png" }
        //ListElement { title: "Outputs"; index: 3; iconSource: "file:/output.png" }
        ListElement { title: "Communication"; index: 2; iconSource: "file:/uart.png" }
    }

    RowLayout
    {
        anchors.fill: parent
        spacing: 5
        Rectangle
        {
            id: menuPanel
            Layout.preferredWidth: 60
            Layout.fillHeight: true
            color: root.color

            ListView
            {
                id: menu
                anchors.fill: parent
                focus: true

                highlightFollowsCurrentItem: true
                highlightMoveDuration: 250

                //KeyNavigation.right: control
                keyNavigationWraps: true
                model: menuModel
                delegate: TabButton
                {

                    hoverEnabled: true

                    ToolTip.delay: 1500
                    ToolTip.timeout: 3000
                    ToolTip.visible: hovered
                    ToolTip.text: title
                    width: parent.width
                    height: menuPanel.height / menu.count
                    font.pixelSize: 14
                    //text: title
                    icon.source: iconSource
                    onClicked:
                    {
                        stack.currentIndex = index;
                    }
                    onCheckedChanged:
                    {
                        if (checked)
                        {
                            icon.width = icon.width  - 6
                            icon.color = Style.color.foreground
                            b.color = "transparent"//Style.color.background
                            shadow.enabled = false
                            shadow.visible = false
                        }
                        else {

                            icon.width = icon.width  + 6

                            icon.color = Style.color.background
                            b.color = Style.color.foreground
                            shadow.enabled = true
                            shadow.visible = true
                        }
                    }

                    background: Rectangle
                    {
                        id: b
                        anchors.fill: parent
                        color: Style.color.foreground
                    }

                    DropShadow
                    {
                        id: shadow
                        enabled: true//shadowEnabled
                        visible: true//shadowEnabled
                        anchors.fill: b
                        horizontalOffset: 2
                        verticalOffset: 2
                        radius: 8.0
                        samples: 17
                        color: "#80000000"
                        source: b
                    }
                }
            }
        }


        StackLayout
        {
            clip: true
            id: stack

            Layout.fillHeight: true
            Layout.fillWidth: true
            currentIndex: 0

            TriggerPatternView
            {
                title: "Trigger pattern title"
                Layout.alignment: Qt.AlignTop
                Layout.fillHeight: true
                Layout.fillWidth: true
                //Layout.margins: 10
            }


            SensorsView2
            {
                id: sensorsView2
                Layout.alignment: Qt.AlignTop
                Layout.fillHeight: true
                Layout.fillWidth: true
                //Layout.margins: 10

            }

            SensorsView
            {
                id: sensorsView
                Layout.alignment: Qt.AlignTop
                Layout.fillHeight: true
                Layout.fillWidth: true
                //Layout.margins: 10

            }


            OutputsView
            {
                Layout.alignment: Qt.AlignTop
                Layout.fillHeight: true
                Layout.fillWidth: true
                //Layout.margins: 10
            }
            InputsView
            {
                Layout.alignment: Qt.AlignTop
                Layout.fillHeight: true
                Layout.fillWidth: true
                //Layout.margins: 10
            }
            ConnectionView
            {
                Layout.alignment: Qt.AlignTop
                Layout.fillHeight: true
                Layout.fillWidth: true
                //Layout.margins: 10
            }


        }

    }


}
