import QtQuick 2.6
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0
import QtQuick.Controls.Material 2.3


Item
{
    id: root

    ScrollView
    {
        anchors.fill: parent
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
            spacing: 0

            // Variable outputs (i2c potentiometers)
            VariableOutputsView
            {
                id: variableOutputsView
                Layout.fillWidth: true
                //Layout.minimumHeight: implicitHeight
                Layout.fillHeight: minimized ? false : true

                model: io.voModel
            }
            // Switchable outputs (on/off)
            SwitchableOutputsView
            {
                id: switchableOutputsView
                Layout.fillWidth: true
                //Layout.preferredHeight: implicitHeight

                model: io.soModel
            }
            // Switchable inputs (on/off)
            SwitchableInputsView
            {
                id: switchableInputsView
                Layout.fillWidth: true
                //Layout.preferredHeight: implicitHeight

                model: io.siModel
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
