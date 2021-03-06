import QtQuick 2.6
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0
import QtQuick.Controls.Material 2.3


ApplicationWindow
{
    id: root
    title: qsTr("Ecustim")
    visible: true

    width: 640
    height: 480

    Material.theme: Material.Dark
    Material.accent: Material.DeepOrange

    ColumnLayout
    {
        anchors.fill: parent
        spacing: 0

        RowLayout
        {
            id: menu
            Layout.alignment: Qt.AlignCenter
            spacing: 0

            RoundButton
            {
                id: buttonConnection
                property int stackIndex: 3
                icon.source: "qrc:/images/link-black-24dp.svg"
                flat: true
                radius: 2
                icon.color: Material.foreground
                display: AbstractButton.IconOnly
                onClicked:
                    menu.toggleButton(stackIndex)
            }

            RoundButton
            {
                id: buttonTrigger
                property int stackIndex: 0
                icon.source: "qrc:/images/settings-black-24dp.svg"

                flat: true
                radius: 2
                icon.color: Material.foreground
                display: AbstractButton.IconOnly
                onClicked:
                    menu.toggleButton(stackIndex)
            }

            RoundButton
            {
                id: buttonVariableHardwareManager
                property int stackIndex: 1
                icon.source: "qrc:/images/compare_arrows-black-24dp.svg"

                flat: true
                radius: 2
                icon.color: Material.foreground
                display: AbstractButton.IconOnly
                onClicked:
                    menu.toggleButton(stackIndex)
            }

            // Please, refacor this
            function toggleButton(selectedStackIndex)
            {
                //
                if (buttonTrigger.stackIndex === selectedStackIndex) {
                    //buttonTrigger.icon.width = 48
                    //buttonTrigger.icon.height = 48
                    buttonTrigger.icon.color = Material.accent
                }
                else {
                    //buttonTrigger.icon.width = 36
                    //buttonTrigger.icon.height = 36
                    buttonTrigger.icon.color = Material.foreground
                }
                //
                if (buttonVariableHardwareManager.stackIndex === selectedStackIndex) {
                    //buttonVariableHardwareManager.icon.width = 48
                    //buttonVariableHardwareManager.icon.height = 48
                    buttonVariableHardwareManager.icon.color = Material.accent
                }
                else {
                    //buttonVariableHardwareManager.icon.width = 36
                    //buttonVariableHardwareManager.icon.height = 36
                    buttonVariableHardwareManager.icon.color = Material.foreground
                }
                //
//                if (buttonVariableHardwareManagerSettings.stackIndex === selectedStackIndex) {
//                    //buttonVariableHardwareManagerSettings.icon.width = 48
//                    //buttonVariableHardwareManagerSettings.icon.height = 48
//                    buttonVariableHardwareManagerSettings.icon.color = Material.accent
//                }
//                else {
//                    //buttonVariableHardwareManagerSettings.icon.width = 36
//                    //buttonVariableHardwareManagerSettings.icon.height = 36
//                    buttonVariableHardwareManagerSettings.icon.color = Material.foreground
//                }
                //
                if (buttonConnection.stackIndex === selectedStackIndex) {
                    //buttonConnection.icon.width = 48
                    //buttonConnection.icon.height = 48
                    buttonConnection.icon.color = Material.accent
                }
                else {
                    //buttonConnection.icon.width = 36
                    //buttonConnection.icon.height = 36
                    buttonConnection.icon.color = Material.foreground
                }
                //
                stack.currentIndex = selectedStackIndex
            }
        }

        StackLayout
        {
            id: stack
            Layout.fillWidth: true
            Layout.fillHeight: true

            clip: true
            currentIndex: 0

            // 1
            TriggerPatternView {
                property int stackIndex: 0
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
            // 2
            InputsOutputsView {
                property int stackIndex: 1
                Layout.fillWidth: true
                Layout.fillHeight: true

                onEditSwitchableInputs:
                {
                    stack.currentIndex = 2
                }
                onEditSwitchableOutputs:
                {
                    stack.currentIndex = 2
                }
                onEditVariableOutputs:
                {
                    stack.currentIndex = 2
                }
            }
            // 3
            InputsOutputsEditView {
                property int stackIndex: 2

                Layout.fillWidth: true
                Layout.fillHeight: true
            }
            // 4
            ConnectionView {
                property int stackIndex: 3
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
        }
    }
}
