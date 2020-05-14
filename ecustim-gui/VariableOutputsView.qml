import QtQuick 2.6
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0
//import QtQuick.Controls.Material 2.3


Item
{
    id: root
    implicitHeight: control.implicitHeight

    ListModel
    {
        id: variableOutputsModel
        ListElement {caption: "RPM"}
        ListElement {caption: "MAP"}
        ListElement {caption: "TPS"}
        ListElement {caption: "IAT"}
        ListElement {caption: "CLT"}
        ListElement {caption: "WBO2"}
    }

    GroupBox
    {
        id: control
        title: "Variable Outputs"
        background: Rectangle{anchors.fill: parent; color: "transparent"; border.color: "transparent"}
        anchors.fill: parent

        RowLayout
        {
            anchors.margins:  -12
            anchors.fill: parent
            clip:true
            spacing: 5

            Repeater
            {
                model: variableOutputsModel
                delegate: VariableOutputItem
                {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.alignment: Qt.AlignCenter
                    caption: model.caption
                }
            }
        }
    }
}
