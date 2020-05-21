import QtQuick 2.6
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0


Item
{
    id: root
    implicitHeight: groupBox.implicitHeight

    property bool minimized: groupBox.minimized
    property variant model: 0

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
                model: root.model
                delegate: VariableOutputItem
                {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.alignment: Qt.AlignCenter

                    visible: model.item.active
                    caption: model.item.description
                    actualValue: model.item.actualValue
                    onSetValueChanged:
                        model.item.setValue = setValue
                }
            }
        }
    }
}
