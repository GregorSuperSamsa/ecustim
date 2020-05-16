import QtQuick 2.6
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0
import QtQuick.Controls.Material 2.3


Item
{
    id:root
    property alias title: groupBox.title
    property alias content: groupBox.contentChildren
    property bool hasBackground: true
    property bool minimized: false
    property real collapsedHeightOffset: 10
    implicitHeight:  minimized ?
                         groupBox.label.implicitHeight + collapsedHeightOffset:
                         groupBox.implicitHeight
    GroupBox
    {
        id: groupBox
        anchors.fill: parent
        clip: true

        label: Label
        {
            id: label
            text: title
            width: parent.availableWidth
            leftPadding: indicator.x + indicator.width + groupBox.leftPadding /2
            elide: Text.ElideRight
            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                    minimized = !minimized
                    indicator.requestPaint()
                }
            }

            Canvas
            {
                id: indicator
                anchors.verticalCenter: parent.verticalCenter
                x: groupBox.leftPadding
                rotation: minimized ? -90 : 0
                width: 12
                height: 8
                contextType: "2d"
                onPaint: {
                    context.reset();
                    context.moveTo(0, 0);
                    context.lineTo(width, 0);
                    context.lineTo(width / 2, height);
                    context.closePath();
                    context.fillStyle = parent.color;
                    context.fill();
                }
            }
        }

        background: Pane
        {
            visible: hasBackground || (minimized && collapsedHeightOffset > 0)
            enabled: hasBackground || (minimized && collapsedHeightOffset > 0)

            y: parent.topPadding - parent.padding
            width: parent.width
            height: parent.height - parent.topPadding + parent.padding

            Material.background: Style.color.foreground
            Material.elevation: visible ? 10 : 0
        }

        Behavior on height
        {
            NumberAnimation { duration: 250 }
        }
    }
}
