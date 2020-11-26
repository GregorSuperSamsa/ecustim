import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12


Item {

    //border.color: "yellow"
    //color: "transparent"

    id: root

    property int contentHeight: (height - rowLayout.implicitHeight)
    property alias content: rect.children
    property alias title: label.text
    property bool minimized: false

    signal buttonClicked()

    implicitHeight: columnLayout.implicitHeight

    ColumnLayout {
        id: columnLayout
        anchors.fill: parent
        spacing: 0

        Rectangle {

            property int defaultHeight: 40
            Layout.fillWidth: true
            //Layout.preferredHeight: defaultHeight
            Layout.minimumHeight: defaultHeight
            Layout.maximumHeight: defaultHeight
            Layout.alignment: Qt.AlignTop
            radius: 2
            color: "transparent"
            border.color: "white"

        RowLayout {
            id: rowLayout
            anchors.fill: parent
//            property int defaultHeight: 40
//            Layout.fillWidth: true
//            //Layout.preferredHeight: defaultHeight
//            Layout.minimumHeight: defaultHeight
//            Layout.maximumHeight: defaultHeight
//            Layout.alignment: Qt.AlignTop
            spacing: 0

            RoundButton {
                id: buttonExpand
                Layout.fillHeight: true
                Layout.preferredWidth: height
                flat: true
                icon.source: minimized ? "qrc:/images/expand_more-black-24dp.svg" : "qrc:/images/expand_less-black-24dp.svg"
                radius: 2
                onClicked:
                {
                    minimized = !minimized
                }
//                background: Rectangle
//                {
//                    anchors.fill: parent
//                    border.color: "red"
//                    color: "transparent"
//                }
            }

            Label {
                id: label
                Layout.fillWidth: true
                Layout.fillHeight: true
                verticalAlignment: Text.AlignVCenter
                clip: true
                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                        buttonExpand.clicked()
                }
//                background: Rectangle
//                {
//                    anchors.fill: parent
//                    border.color: "red"
//                    color: "transparent"
//                }
            }

            RoundButton {
                id: buttonSettings
                Layout.fillHeight: true
                Layout.preferredWidth: height
                flat: true
                radius: 2
                icon.source: "qrc:/images/build-black-24dp.svg"
                onClicked:
                    buttonClicked()
//                background: Rectangle
//                {
//                    anchors.fill: parent
//                    border.color: "red"
//                    color: "transparent"
//                }
            }
        }
    }

        Item {
            implicitHeight: minimized ? 0 : childrenRect.height
            //border.color: "white"
            //color: "transparent"
            id: rect
            Layout.fillWidth: true
            Layout.preferredHeight: implicitHeight
            clip: true
        }
    }
}
