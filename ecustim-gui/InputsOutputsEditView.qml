import QtQuick 2.6
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0
import QtQuick.Controls.Material 2.3

import QtQuick 2.12
import QtCharts 2.1
import QtQuick.Controls 2.0


Item
{
    id: root

    ColumnLayout {
        anchors.fill: parent

        Label {
            Layout.fillWidth: true
            Layout.preferredHeight: implicitHeight
            text: "Variable outputs"
            elide: Text.ElideRight
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.preferredHeight: implicitHeight
            spacing: 0

            ComboBox {
                id: combo
                Layout.fillWidth: true
                Layout.preferredHeight: implicitHeight

                spacing: 10
                model: io.voModel
                displayText: currentText

                delegate: ItemDelegate
                {
                    width: combo.width
                    id: control
                    text: item.description
                    highlighted: (combo.currentIndex === index)
                    onClicked: combo.displayText = text

                    RoundButton {
                        id: buttonDelete
                        height: combo.height
                        width: height
                        anchors.right: parent.right
                        flat: true
                        radius: 3
                        icon.source: "qrc:/clear-black-24dp.svg"
                    }
                }
            }

            RoundButton {
                id: buttonAdd
                Layout.preferredHeight: implicitHeight
                Layout.preferredWidth: implicitWidth

                flat: true
                icon.source: "qrc:/add-black-24dp.svg"
                radius: 3
                onClicked: {
                    //TODO
                }
            }
        }

        ColumnLayout {
            Layout.fillHeight: true
            Layout.fillWidth: true

            Label {
                id: labelName
                Layout.fillWidth: true
                Layout.preferredHeight: contentHeight

                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
                text: "Name"
            }

            TextField {
                id: textFieldCaption
                Layout.fillWidth: true
                Layout.preferredHeight: implicitHeight
                Layout.alignment: Qt.AlignHCenter

                font.pixelSize: labelName.font.pixelSize
                placeholderText: "Set a descriptive name for this item"
            }

            Label {
                Layout.fillWidth: true
                Layout.preferredHeight: contentHeight

                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
                text: "Resistance range [\u03A9]"
            }

            RowLayout {
                Layout.preferredHeight: implicitHeight
                Layout.fillWidth: true

                TextField {
                    id: textFieldMinResistance
                    Layout.preferredWidth: 80
                    Layout.preferredHeight: implicitHeight
                    Layout.leftMargin:  5

                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter

                    text: resistanceRange.first.value.toFixed(0)
                }

                Item {
                    Layout.fillWidth: true
                }

                TextField {
                    id: textFieldMaxResistance
                    Layout.preferredWidth: 80
                    Layout.preferredHeight: implicitHeight
                    Layout.rightMargin: 5

                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignTop

                    text: resistanceRange.second.value.toFixed(0)
                }
            }

            RangeSlider {
                id: resistanceRange
                Layout.alignment: Qt.AlignRight
                Layout.preferredHeight: implicitHeight
                Layout.fillWidth: true
                from: 0
                to: 100
                first.value: 25
                second.value: 75
            }




            Label {
                id: labelIdentifier
                Layout.fillWidth: true
                Layout.preferredHeight: contentHeight

                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
                text: "Identifier"
            }

            TextField {
                id: textFieldIdentifier
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredHeight: implicitHeight
                font.pixelSize: labelIdentifier.font.pixelSize
                placeholderText: "I2C address of the digital potentiometer"
            }



            CheckBox {
                id: checkboxEnabled
                Layout.preferredWidth: implicitWidth
                Layout.preferredHeight: implicitHeight
                checked: false
                text: "Enable"
            }

            RoundButton {
                id: buttonSave
                Layout.alignment: Qt.AlignBottom | Qt.AlignHCenter
                Layout.fillWidth: true
                Layout.preferredHeight: implicitHeight
                flat: true
                icon.source: "qrc:/save-black-48dp.svg"
                radius: 3
                onClicked: { }
            }
        }
    }
}
