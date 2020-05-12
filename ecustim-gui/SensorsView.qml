import QtQuick 2.6
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0
//import QtQuick.Controls.Material 2.3


View
{
    id: root
    title: "Sensors"

    content: ScrollView
    {
        id: control
        anchors.fill: parent
        clip: true

        ColumnLayout
        {
            anchors.margins: 10
            width: root.width
            spacing: 10
            GroupBox
            {
                background: Rectangle
                {
                    anchors.fill: parent
                    color: root.backgroundColor
                }

                id: group1
                title: "Simulation"

                Layout.margins: 10
                Layout.alignment: Qt.AlignTop
                Layout.fillWidth: true

                Flow
                {
                    id: flow
                    anchors.fill: parent
                    spacing: 20
                    Repeater
                    {
                        model: 5
                        delegate: SensorItem
                        {
                            caption: "TPS"
                        }
                    }
                }
            }

            GroupBox
            {
                background: Rectangle
                {
                    anchors.fill: parent
                    color: root.backgroundColor
                }

                id: group2
                title: "IOs"

                Layout.margins: 20
                Layout.alignment: Qt.AlignTop
                Layout.fillWidth: true

                SensorItem2
                {
                caption: "MAP"
                anchors.fill: parent
                }

                Flow
                {
                    id: flow2
                    anchors.fill: parent
                    spacing: 20
                    Repeater
                    {
                        model: 5
                        delegate: SensorItem
                        {
                            caption: "TPS"
                        }
                    }
                }
            }
        }
    }
}
