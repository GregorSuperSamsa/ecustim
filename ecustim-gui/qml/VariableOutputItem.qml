import QtQuick 2.12
import QtQuick.Controls 2.5


Rectangle
{
    id: root
    color: "transparent"
    property string caption: ""
    property real setValue: 0
    property string valueUnits: "[\u03A9]"
    property real actualValue: 0
    property real i2cAddress: 0xFF


    Label {
        id: labelValue
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

        horizontalAlignment: Qt.AlignHCenter
        verticalAlignment: Qt.AlignVCenter
        text: sliderSetValue.value.toFixed(0)
    }

    Slider {
        id: sliderSetValue
        anchors.top: labelValue.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: labelCaption.top

        from: 0
        to: 111
        stepSize: 1
        orientation: Qt.Vertical
        onValueChanged: setValue = value
    }

    Label {
        id: labelCaption
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        horizontalAlignment: Qt.AlignHCenter
        verticalAlignment: Qt.AlignVCenter
        text: caption + " " + valueUnits
    }
}

































//import QtQuick 2.12
//import QtQuick.Controls 2.5
//import QtQuick.Layouts 1.12


//Rectangle
//{
//    id: root
//    anchors.fill: parent

//    property string caption: ""
//    property real setValue: 0
//    property string valueUnits: "[\u03A9]"
//    property real actualValue: 0
//    property real i2cAddress: 0xFF

//    implicitHeight: columnLayout.implicitHeight
//    implicitWidth: columnLayout.implicitWidth

//    ColumnLayout {
//        id: columnLayout
//        spacing: 0
//        anchors.fill: parent
//        anchors.topMargin: 5
//        anchors.bottomMargin:  5

//        Label {
//            id: labelValue
//            Layout.alignment: Qt.AlignHCenter
//            text: sliderSetValue.value.toFixed(0)
//        }

//        Slider {
//            id: sliderSetValue
//            Layout.fillHeight: true
//            Layout.fillWidth: true

//            from: 0
//            to: 111
//            stepSize: 1
//            orientation: Qt.Vertical
//            onValueChanged: setValue = value
//        }

//        Label {
//            id: labelCaption
//            Layout.alignment: Qt.AlignHCenter
//            text: caption + " " + valueUnits
//        }
//    }
//}
