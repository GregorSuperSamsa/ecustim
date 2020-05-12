import QtQuick 2.12
import QtCharts 2.1
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0
import '.'
import QtQuick.Controls.Material 2.3


Item
{



    // Drop shadow effect
    property bool shadowEnabled: false
    // Title of the view
    property string title: ""
    property int titleFontSizePx: 22
    // Source of the icon
    property string iconSource: ""
    // Colors
    property color backgroundColor:  "#ECEFF1"//Style.color.background//"#ffffff" // "#303030"
    property color headerColor:     "#404040"
    property color fontColor:       Style.font.color
    // Placeholder
    default property alias content: placeholder.data

    Rectangle
    {
        id: root
        color: "transparent"
        anchors.fill: parent

        ColumnLayout
        {
            anchors.fill: parent
            spacing: 0

//            Text
//            {

//                id: caption
//                Layout.alignment: Qt.AlignLeft
//                Layout.preferredHeight: contentHeight
//                Layout.margins: 10
//                Layout.fillWidth: true
//                text: title
//                color: Material.foreground
//                //font.pixelSize: titleFontSizePx
//                verticalAlignment: Text.AlignVCenter
//            }

            Item
            {
                Layout.alignment: Qt.AlignCenter
                Layout.fillWidth: true
                Layout.fillHeight: true
                id: placeholder
            }
        }
    }

    DropShadow
    {
        enabled: shadowEnabled
        visible: shadowEnabled
        anchors.fill: root
        horizontalOffset: 3
        verticalOffset: 3
        radius: 8.0
        samples: 17
        color: "#80000000"
        source: root
    }
}
