import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12


Item
{
    id: root

    ScrollView
    {
        anchors.fill: parent
        contentHeight: Math.max(root.height, columnLayout.implicitHeight)
        contentWidth: parent.width
        clip: true
        ScrollBar.vertical.interactive: true

        ColumnLayout
        {
            id: columnLayout
            anchors.fill: parent
            anchors.leftMargin: 10
            anchors.rightMargin: 10
            spacing: 0

            Label
            {
                Layout.fillWidth: true
                //Layout.preferredHeight: implicitHeight
                text: "Variable outputs"
            }

            RowLayout
            {
                Layout.fillWidth: true
                //Layout.preferredHeight: implicitHeight
                spacing: 0

                ComboBox
                {
                    id: combo
                    Layout.fillWidth: true
                    //Layout.preferredHeight: implicitHeight

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
                            radius: 2
                            icon.source: "qrc:/images/clear-black-24dp.svg"
                        }
                    }
                }

                RoundButton {
                    id: buttonAdd
                    Layout.preferredHeight: implicitHeight
                    Layout.preferredWidth: implicitWidth

                    flat: true
                    icon.source: "qrc:/images/add-black-24dp.svg"
                    radius: 2
                    onClicked: {
                        //TODO
                    }
                }
            }

            ColumnLayout {
                Layout.fillHeight: true
                Layout.fillWidth: true

                CheckBox {
                    id: checkboxEnabled
                    Layout.preferredWidth: implicitWidth
                    Layout.preferredHeight: implicitHeight
                    checked: false
                    text: "Use this item"
                }

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

                        inputMethodHints: Qt.ImhDigitsOnly
                        validator: IntValidator {bottom: 0; top: resistanceRange.second.value.toFixed(0)}

                        onEditingFinished:
                        {
                            resistanceRange.first.value = parseInt(text)
                        }
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

                        inputMethodHints: Qt.ImhDigitsOnly
                        validator: IntValidator {bottom: resistanceRange.first.value.toFixed(0); top: 100}

                        onEditingFinished:
                        {
                            resistanceRange.second.value = parseInt(text)
                        }
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

                Item {
                    id: spacer
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                }

                RowLayout
                {
                    Layout.fillWidth: true
                    Layout.preferredHeight: implicitHeight

                    Button
                    {
                        Layout.fillWidth: true
                        text: "Cancel"
                    }
                    Button
                    {
                        Layout.fillWidth: true
                        text: "Save"
                    }
                }
            }
        }
    }
}
