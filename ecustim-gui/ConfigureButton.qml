import QtQuick 2.9
import QtQuick.Extras 1.4
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.3

Item {

    RoundButton
    {
        width: 40
        height: 40
        anchors.centerIn: parent
        text: "..."
        ToolTip.delay: 1500
        ToolTip.timeout: 3000
        ToolTip.visible: hovered
        ToolTip.text: "Configure..."
   }

}
