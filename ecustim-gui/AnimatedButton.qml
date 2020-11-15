import QtQuick 2.6
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.12
import QtQuick.Controls.Material 2.3
import QtQml.Models 2.2
import QtGraphicalEffects 1.0
import '.'


Rectangle {
    id: animatedButton
color: "transparent"
    property alias iconImage:     iconImage_
    property alias iconOverlay:   iconOverlay
    property alias button:        button

    signal animatedClicked()

    Image {
        id: iconImage_
        anchors.centerIn: parent
    }

    ColorOverlay {
        id: iconOverlay
        anchors.fill: iconImage_
        source: iconImage_
        color: "red"
    }

    RoundButton
    {
        id: button
        anchors.fill: parent
        flat: true
        radius: 4
        MouseArea {
            anchors.fill: parent
            onClicked:
                animatedClicked();
        }
    }
}

