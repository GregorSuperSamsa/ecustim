import QtQuick 2.6
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0


Item {

    id: root
    implicitHeight: groupBox.implicitHeight
    implicitWidth: groupBox.implicitWidth

    property bool minimized: groupBox.minimized
    property variant model: 0

    signal edit()

    CollapsableGroupBox {
        id: groupBox
        anchors.fill: parent
        title: "Variable Outputs"

        content: Flow {
            id: flow
            width: parent.width
            spacing: 0

            Repeater
            {
                id: repeater
                model: root.model
                delegate:
                    VariableOutputItem {
                    width:   Math.max((flow.width - flow.spacing * (repeater.model.count - 1)) / repeater.model.count, implicitWidth)

                    height: Math.max(groupBox.contentHeight, 200)
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

                ////                console.log("MaxImplicitWidth:" + maxImplicitWidth);
                ////                console.log("GroupBoxImplicitHeight:" + root.implicitHeight);
            }
        }
        onButtonClicked:
        {
            edit()
        }
    }
}
