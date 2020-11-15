import QtQuick 2.6
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0
import QtQuick.Controls.Material 2.3


Item
{
    id: root
    implicitHeight: groupBox.implicitHeight

    property variant model: 0

    CollapsableGroupBox
    {
        id: groupBox
        anchors.fill: parent
        //hasBackground: true
        hasBackground: false
        title: "Switchable Outputs"

        content: Flow
        {
            id: flow
            anchors.fill: parent
            spacing: 10
            padding: 0

            Repeater
            {
                id: repeater
                model: root.model
                delegate: SwitchableOutputItem
                {
                    width:   Math.max((flow.width - flow.spacing * (repeater.model.count - 1)) / repeater.model.count, implicitWidth)

                    visible: model.item.active
                    caption: model.item.description
                    actualValue: model.item.actualValue
                    onSetValueChanged:
                        model.item.setValue = setValue
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

