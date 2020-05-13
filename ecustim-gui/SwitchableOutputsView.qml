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
        anchors.fill: parent
        title: "Switchable Outputs"

        background: Pane
        {
            y: control.topPadding - control.padding
            width: parent.width
            height: parent.height - control.topPadding + control.padding

            Material.background: Style.color.foreground
            Material.elevation: 10
        }

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

