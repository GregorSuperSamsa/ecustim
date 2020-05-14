import QtQuick 2.6
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0
import QtQuick.Controls.Material 2.3

Item
{
    id: root
    implicitHeight: control.implicitHeight

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
        id: control
        anchors.fill: parent
        title: "Switchable Outputs"

        background: Pane
        {
            y: control.topPadding - control.padding
            width: parent.width
            height: parent.height - control.topPadding + control.padding

            Material.background: Style.color.foreground
            Material.elevation: 10
        }

        Flow
        {
            id: flow
            anchors.fill: parent
            spacing: 0
            padding: 0

            Repeater
            {
                model: switchableOutputsModel
                delegate: SwitchableOutputItem
                {
                    width:   Math.max(flow.width / (switchableOutputsModel.count), implicitWidth)
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

