import QtQuick 2.6
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0
import QtQuick.Controls.Material 2.3

Item
{

id: root

implicitHeight: control.implicitHeight

    GroupBox
    {
        id: control
        title: "Switchable Outputs"
        Material.background: Style.color.foreground
        Material.elevation: 10

        //height: flow.implicitHeight
        anchors.fill: parent
        //                        topPadding: 0
        //                        leftPadding: 0
        //                        rightPadding: 0
        //                        bottomPadding: 0




        //spacing: 0
        Flow
        {
            id: flow
            anchors.fill: parent
            spacing: 5
            padding: 0

onImplicitHeightChanged:
{
    console.log("Flow " + implicitHeight)
    console.log("Groupbox content" + control.implicitContentHeight)
    console.log("Groupbox control" + control.implicitHeight)
    console.log("Groupbox bck" + control.implicitBackgroundHeight)
    console.log("Item " + root.implicitHeight)
}



            OutputItem
            {
            }

            OutputItem
            {
            }
            OutputItem
            {
            }
            OutputItem
            {
            }
            OutputItem
            {
            }


        }
    }
}

