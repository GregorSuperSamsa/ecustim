import QtQuick 2.6
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0
import QtQuick.Controls.Material 2.3


Item
{
    id: root

    ScrollView
    {
        ScrollBar.vertical.interactive: true

        anchors.fill: parent
        clip: true
        contentHeight: Math.max(root.height,
                                columnLayout.anchors.topMargin +
                                columnLayout.anchors.bottomMargin +
                                columnLayout.implicitHeight)
        ColumnLayout
        {
            id: columnLayout
            anchors.margins:  5
            anchors.fill: parent
            spacing: 5

            VariableOutputsView
            {
                id: variableOutputsView
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.preferredHeight: implicitHeight

                property real previousImplicitHeigth: 0
                onImplicitHeightChanged:
                {
                    Layout.fillHeight = (implicitHeight > previousImplicitHeigth) ? true : false
                    previousImplicitHeigth = implicitHeight
                }
                Component.onCompleted:
                {
                    previousImplicitHeigth = implicitHeight
                }
            }

            SwitchableOutputsView
            {
                id: switchableOutputsView
                Layout.fillWidth: true
                Layout.preferredHeight: implicitHeight
            }

            SwitchableInputsView
            {
                id: switchableInputsView
                Layout.fillWidth: true
                Layout.preferredHeight: implicitHeight
            }

            Item
            {
                id: spacer
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
        }
    }
}
