import QtQuick 2.10


Item
{
    id: root
    implicitHeight: groupBox.implicitHeight

    property variant model: 0

    signal edit()

    ListModel
    {
        id: switchableInputsModel
        ListElement {caption: "Input 1"}
        ListElement {caption: "Input 2"}
        ListElement {caption: "Input 3"}
        ListElement {caption: "Injector 1"}

    }

    CollapsableGroupBox {
        id: groupBox
        anchors.fill: parent
        title: "Switchable Inputs"

        content: Flow
        {
            id: flow
            width: parent.width
            spacing: 0

            Repeater
            {
                id: repeater
                model: root.model
                delegate: SwitchableInputItem
                {
                    width:   Math.max((flow.width - flow.spacing * (repeater.model.count - 1)) / repeater.model.count, implicitWidth)
                    caption: model.item.description
                    active: model.item.actualValue
                }
            }
            // TODO: Probably, this snippet should be moved in the model code
            Component.onCompleted:
            {
                var maxImplicitWidth = 0;
                for (var i = 0; i < children.length; ++i) {
                    maxImplicitWidth = Math.max(maxImplicitWidth, flow.children[i].implicitWidth)
                }

                for (var j = 0; j < children.length; ++j) {
                    children[j].implicitWidth = maxImplicitWidth
                }
            }
        }
        onButtonClicked:
        {
            edit()
        }
    }
}
