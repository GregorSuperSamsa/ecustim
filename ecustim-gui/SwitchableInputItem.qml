import QtQuick 2.9
import QtQuick.Extras 1.4
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.3

Item
{
    id: root
    implicitHeight: columnLayout.implicitHeight
    implicitWidth: columnLayout.implicitWidth

    property string caption: ""
    property bool active: false
    property color activeColor : Material.color(Material.Red, Material.Shade600)
    property color inactiveColor : Material.color(Material.Grey, Material.Shade800)

    onActiveChanged:
    {
        if (active)
        {
            anime.stop()
            anime.to = activeColor
            anime.duration = 300
            anime.start()

            anime1.stop()
            anime1.to = activeColor
            anime1.duration = 300
            anime1.start()
        }
        else
        {
            anime.stop()
            anime.to = inactiveColor
            anime.duration = 100
            anime.start()

            anime1.stop()
            anime1.to = inactiveColor
            anime1.duration = 100
            anime1.start()

        }
    }

    ColumnLayout {
        id: columnLayout
        anchors.fill: parent
        spacing: 0

        Rectangle
        {
            id: statusIndicatorPlaceholder
            Layout.preferredHeight:  30
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignCenter
            color: "transparent"

            Rectangle
            {
                id: statusIndicator
                anchors.centerIn: parent
                implicitHeight:  30
                implicitWidth: 30


                radius: height /2
                color: "transparent"
                border.color: Material.color(Material.Red, Material.Shade600)
                border.width: 3

                ColorAnimation on border.color
                {
                    id: anime
                    running: false
                }

                Rectangle
                {
                    anchors.fill: parent
                    anchors.margins: 7
                    radius: height /2
                    color: statusIndicator.border.color

                    ColorAnimation on color
                    {
                        id: anime1
                        running: false
                    }
                }
            }
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
            //wrapMode: Text.WordWrap

            text: caption

            // Test purposes only
            MouseArea
            {
                anchors.fill: parent
                onClicked:
                    active = !active;
            }
        }
    }
}
