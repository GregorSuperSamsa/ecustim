import QtQuick 2.9
import QtQuick.Extras 1.4
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.3

Item {
    id: root

    ColumnLayout {
        id: columnLayout
        anchors.fill: parent
        spacing: 0
        //                Rectangle
        //                {
        //                    id: r1
        //                    Layout.fillHeight: true
        //                    Layout.fillWidth: true
        //                    color: "red"
        //                    Layout.margins: 10
        //                }

        //                Label
        //                {
        //                    id: r2
        //                    Layout.fillHeight: true
        //                    Layout.fillWidth: true
        //                    //color: "blue"
        //                    text: "Injector output 1"
        //                    Layout.margins: 10
        //                    wrapMode: Text.WordWrap
        //                }

        //        StatusIndicator
        //        {
        //            id: statusIndicator
        //            Layout.fillHeight: true
        //            Layout.fillWidth: true
        //            active: true
        //            color: Material.color(Material.Red, Material.Shade700)
        //        }

        Rectangle
        {
            id: statusIndicator
            Layout.fillHeight: true
            Layout.fillWidth: true

            radius: 10
//            background: Rectangle {
//                color: Material.color(Material.Red, Material.Shade700)
//            }
        }

        Label
        {
            id: label
            Layout.fillHeight: true
            Layout.fillWidth: true
            text: "Injector output 1"
            horizontalAlignment: Text.AlignHCenter
            wrapMode: Text.WordWrap

        }
    }
}
