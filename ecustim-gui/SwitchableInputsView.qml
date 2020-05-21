import QtQuick 2.6
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0
import QtQuick.Controls.Material 2.3


Item
{
    id: root
    implicitHeight: groupBox.implicitHeight

    ListModel
    {
        id: switchableInputsModel
        ListElement {caption: "Input 1"}
        ListElement {caption: "Input 2"}
        ListElement {caption: "Input 3"}
        ListElement {caption: "Injector 1"}

    }

    CollapsableGroupBox
    {
        id: groupBox
        anchors.fill: parent
        hasBackground: true
        title: "Switchable Inputs"

        content: Flow
        {
            id: flow
            anchors.fill: parent
            spacing: 10
            padding: 0

            Repeater
            {
                model: switchableInputsModel
                delegate: SwitchableInputItem
                {
                    width:   Math.max((flow.width - flow.spacing * (switchableInputsModel.count - 1)) / switchableInputsModel.count, implicitWidth)
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



//Item
//{
//    id: root
//    implicitHeight: control.implicitHeight

//    ListModel
//    {
//        id: switchableInputsModel
//        ListElement {caption: "Input 1"}
//        ListElement {caption: "Input 2"}
//        ListElement {caption: "Input 3"}
//        ListElement {caption: "Injector 1"}
//    }

//    GroupBox
//    {
//        id: control
//        anchors.fill: parent
//        title: "Switchable Inputs"

//        background: Pane
//        {
//            y: control.topPadding - control.padding
//            width: parent.width
//            height: parent.height - control.topPadding + control.padding

//            Material.background: Style.color.foreground
//            Material.elevation: 10
//        }

//        Flow
//        {
//            id: flow
//            anchors.fill: parent
//            spacing: 10
//            padding: 0

//            Repeater
//            {
//                model: switchableInputsModel
//                delegate: SwitchableInputItem
//                {
//                    width:   Math.max((flow.width - flow.spacing * (switchableInputsModel.count - 1)) / switchableInputsModel.count, implicitWidth)
//                    caption: model.caption
//                }
//            }
//            // TODO: Probably, this snippet should be moved in the model code
//            Component.onCompleted:
//            {
//                var maxImplicitWidth = 0;
//                for (var i = 0; i < children.length; ++i)
//                {
//                    maxImplicitWidth = Math.max(maxImplicitWidth, flow.children[i].implicitWidth)
//                }

//                for (var j = 0; j < children.length; ++j)
//                {
//                    children[j].implicitWidth = maxImplicitWidth
//                }
//                //flow.forceLayout()
//            }
//        }
//    }
//}
