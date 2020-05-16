import QtQuick 2.6
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0
import QtQuick.Controls.Material 2.3

Item
{
    id: root
    property bool minimized: false

    implicitHeight: minimized ? groupBox.label.implicitHeight + 10 : groupBox.implicitHeight
    clip: true

    ListModel
    {
        id: switchableOutputsModel
        ListElement {caption: "Trigger 1"}
        ListElement {caption: "Trigger 2"}
        ListElement {caption: "Launch control"}
        ListElement {caption: "Trigger 3"}
    }

    GroupBox
    {
        id: groupBox
        anchors.fill: parent
        title: "Switchable Outputs"
        Behavior on height { NumberAnimation { duration: 250 } }

        label: Label
        {
            Canvas
            {
                id: indicatorCanvas
                anchors.verticalCenter: parent.verticalCenter
                x: groupBox.leftPadding
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

            id: label
            width: groupBox.availableWidth
            text: groupBox.title
            leftPadding: indicatorCanvas.x + indicatorCanvas.width + groupBox.leftPadding /2
            elide: Text.ElideRight
            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                    minimized = !minimized
                    indicatorCanvas.rotation = minimized ? -90 : 0
                    indicatorCanvas.requestPaint()
                }
            }
        }

        background: Pane
        {
            y: parent.topPadding - parent.padding
            width: parent.width
            height: parent.height - parent.topPadding + parent.padding

            Material.background: Style.color.foreground
            Material.elevation: 10
        }

        Flow
        {
            id: flow
            anchors.fill: parent
            spacing: 10
            padding: 0

            Repeater
            {
                model: switchableOutputsModel
                delegate: SwitchableOutputItem
                {
                    width:   Math.max((flow.width - flow.spacing * (switchableOutputsModel.count - 1)) / switchableOutputsModel.count, implicitWidth)
                    caption: model.caption
                }
            }
            // TODO: Probably, this snippet should be moved in the model code
            Component.onCompleted:
            {
                var maxImplicitWidth = 0;
                for (var i = 0; i < children.length; ++i)
                {
                    maxImplicitWidth = Math.max(maxImplicitWidth, flow.children[i].implicitWidth)
                }

                for (var j = 0; j < children.length; ++j)
                {
                    children[j].implicitWidth = maxImplicitWidth
                }
                //flow.forceLayout()
            }
        }
    }
}

