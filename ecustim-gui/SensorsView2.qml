import QtQuick 2.6
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0
import QtQuick.Controls.Material 2.3


View
{
    id: root
    content: ScrollView
    {
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
                Layout.minimumHeight: 200
            }

            SwitchableOutputsView
            {
                id: switchableOutputsView
                Layout.fillWidth: true
                Layout.preferredHeight: implicitHeight
            }
        }
    }
}
