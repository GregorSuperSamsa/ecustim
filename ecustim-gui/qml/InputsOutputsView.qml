import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12


Item
{
    id: root

    signal editVariableOutputs()
    signal editSwitchableOutputs()
    signal editSwitchableInputs()

    ScrollView
    {
        //anchors.fill: parent
        width: root.width
        height: root.height
        contentHeight: Math.max(root.height, columnLayout.implicitHeight)
        //columnLayout.anchors.topMargin +
        //columnLayout.anchors.bottomMargin +
        //columnLayout.implicitHeight)
        clip: true
        ScrollBar.vertical.interactive: true

        ColumnLayout
        {
            id: columnLayout
            anchors.fill: parent
            anchors.leftMargin: 10
            anchors.rightMargin:  10
            anchors.bottomMargin:  0
            spacing: 10

            // Variable outputs (i2c potentiometers)
            VariableOutputsView
            {
                id: variableOutputsView
                Layout.fillWidth: true
                //Layout.minimumHeight: implicitHeight
                Layout.fillHeight: minimized ? false : true

                model: io.voModel
                onEdit:
                {
                    editVariableOutputs()
                }
            }
            // Switchable outputs (on/off)
            SwitchableOutputsView
            {
                id: switchableOutputsView
                Layout.fillWidth: true
                //Layout.preferredHeight: implicitHeight

                model: io.soModel
                onEdit:
                {
                    editSwitchableOutputs()
                }
            }
            // Switchable inputs (on/off)
            SwitchableInputsView
            {
                id: switchableInputsView
                Layout.fillWidth: true
                //Layout.preferredHeight: implicitHeight

                model: io.siModel
                onEdit:
                {
                    editSwitchableInputs()
                }
            }
            // Dummy spacer
            Item
            {
                id: spacer
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
        }
    }
}
