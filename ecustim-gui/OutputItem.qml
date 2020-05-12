import QtQuick 2.9
import QtQuick.Extras 1.4
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.3

Item {
    id: root

    ColumnLayout
    {
        id: columnLayout
        anchors.fill: parent
        spacing: 0

        Switch {
            id: switche
            Layout.topMargin: 5
            //text: "Fuel pump"
            Layout.alignment: Qt.AlignCenter
//            Layout.fillHeight: true
            Layout.fillWidth: true
            rotation: 270
            Layout.preferredHeight: 30
//            Layout.preferredWidth: 30
        }

        Label
        {
            Layout.fillWidth: true
            Layout.preferredWidth: contentWidth
            Layout.topMargin: 5

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            text: "Fuel pump relay"
            //fontSizeMode: Text.VerticalFit
            wrapMode: Text.WordWrap
        }

    }
}
