import QtQuick 2.6
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0
//import QtQuick.Controls.Material 2.3


Item
{
    id: root
    implicitHeight: groupBox.implicitHeight
    property bool minimized: groupBox.minimized

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

    CollapsableGroupBox
    {
        id: groupBox
        anchors.fill: parent
        hasBackground: false
        title: "Variable Outputs"

        content: RowLayout
        {
            anchors.margins: -11
            anchors.fill: parent
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
