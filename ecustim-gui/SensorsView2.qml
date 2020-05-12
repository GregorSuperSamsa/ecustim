import QtQuick 2.6
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0
import QtQuick.Controls.Material 2.3


View
{
    id: root

    ColumnLayout
    {
        anchors.margins: 5
        anchors.fill: parent
        spacing: 5

        RowLayout
        {
            id: row1
            //Layout.alignment: Qt.AlignCenter
            clip:true
            //anchors.fill: parent
            Layout.fillWidth: true
            Layout.preferredHeight: parent.height * 0.7
            spacing: 5

            //            ConfigureButton
            //            {
            //                Layout.preferredWidth: 50
            //                Layout.preferredHeight: 50
            //                Layout.alignment: Qt.AlignCenter
            //            }

            SensorItem2
            {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignCenter
                caption: "RPM"
            }

            SensorItem2
            {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignCenter
                caption: "MAP"
            }
            SensorItem2
            {
                Layout.fillWidth: true
                Layout.fillHeight: true
                // Layout.preferredWidth: 100
                Layout.alignment: Qt.AlignCenter
                caption: "TPS"
            }
            SensorItem2
            {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignCenter
                caption: "IAT"
            }
            SensorItem2
            {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignCenter
                caption: "CLT"
            }
            SensorItem2
            {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignCenter
                caption: "O2"
            }
        }




        Pane
        {
            id: row2
            padding: 4

            Layout.fillWidth: true
            Layout.preferredHeight:  parent.height * 0.15
            Layout.minimumHeight: 70
            Material.background: Style.color.foreground
            Material.elevation: 10

            RowLayout
            {
                anchors.fill: parent
                spacing: 0

                //            ConfigureButton
                //            {
                //                Layout.preferredWidth: 50
                //                Layout.preferredHeight: 50
                //                Layout.alignment: Qt.AlignCenter
                //            }

                InputItem2
                {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    //Layout.preferredHeight:
                    //Layout.preferredHeight: 50
                    Layout.alignment: Qt.AlignCenter
                }

                InputItem2
                {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    //Layout.preferredHeight:
                    //Layout.preferredHeight: 50
                    Layout.alignment: Qt.AlignCenter
                }

                InputItem2
                {Layout.fillWidth: true
                    Layout.fillHeight: true
                    //Layout.preferredHeight:
                    //Layout.preferredHeight: 50
                    Layout.alignment: Qt.AlignCenter
                }

                InputItem2
                {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    //Layout.preferredHeight:
                    //Layout.preferredHeight: 50
                    Layout.alignment: Qt.AlignCenter
                }

                InputItem2
                {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    //Layout.preferredHeight:
                    //Layout.preferredHeight: 50
                    Layout.alignment: Qt.AlignCenter
                }

                InputItem2
                {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    //Layout.preferredHeight:
                    //Layout.preferredHeight: 50
                    Layout.alignment: Qt.AlignCenter
                }
                InputItem2
                {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    //Layout.preferredHeight:
                    //Layout.preferredHeight: 50
                    Layout.alignment: Qt.AlignCenter
                }
                InputItem2
                {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    //Layout.preferredHeight:
                    //Layout.preferredHeight: 50
                    Layout.alignment: Qt.AlignCenter
                }
                InputItem2
                {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    //Layout.preferredHeight:
                    //Layout.preferredHeight: 50
                    Layout.alignment: Qt.AlignCenter
                }
                InputItem2
                {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    //Layout.preferredHeight:
                    //Layout.preferredHeight: 50
                    Layout.alignment: Qt.AlignCenter
                }
            }
        }

        Pane
        {
            id: row3
            padding: 4

            Layout.fillWidth: true
            Layout.preferredHeight:  parent.height * 0.15
            Layout.minimumHeight: 70

            Material.background: Style.color.foreground
            Material.elevation: 10

            //spacing: 0
            RowLayout
            {
                anchors.fill: parent
                spacing: 5


                //            ConfigureButton
                //            {
                //                Layout.preferredWidth: 50
                //                Layout.preferredHeight: 50
                //                Layout.alignment: Qt.AlignCenter
                //            }

                OutputItem
                {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    //Layout.preferredHeight:
                    //Layout.preferredHeight: 50
                    Layout.alignment: Qt.AlignCenter
                }

                OutputItem
                {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    //Layout.preferredHeight: 50
                    //Layout.fillHeight: true
                    //Layout.preferredHeight: root.height * 0.3
                    Layout.alignment: Qt.AlignCenter
                }

                OutputItem
                {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    //Layout.preferredHeight: 50
                    //Layout.preferredHeight:
                    //Layout.preferredHeight: 50
                    Layout.alignment: Qt.AlignCenter
                }

                OutputItem
                {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    //Layout.preferredHeight: 50
                    //Layout.fillHeight: true
                    //Layout.preferredHeight: root.height * 0.3
                    Layout.alignment: Qt.AlignCenter
                }

            }
        }
    }
}
