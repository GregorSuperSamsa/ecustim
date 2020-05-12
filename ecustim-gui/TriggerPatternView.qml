import QtQuick 2.12
import QtCharts 2.1
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0
import QtQuick.Controls.Material 2.3

View
{
    property color camGraphColor: Material.color(Material.Teal)//"#e53935"
    property color crankGraphColor: Material.accent//"#6f79a8"

    title: "Trigger patterns"

    content: ColumnLayout
    {
        anchors.fill: parent
        ComboBox
        {
            Layout.alignment: Qt.AlignTop
            Layout.fillWidth: true
            Layout.leftMargin: 5
            Layout.rightMargin: 5
            //height: 30
            id: control
            model: testis.patterns
            //indicator.x: control.spacing
//            delegate: ItemDelegate
//            {
//                width: control.width
//                contentItem: Text
//                {
//                    text: modelData
//                    //color: "#21be2b"
////                    color: headerColor
////                    font: control.font
//                    elide: Text.ElideRight
//                    verticalAlignment: Text.AlignVCenter
//                }
//                highlighted: control.highlightedIndex == index
//            }

            //            contentItem: Text {
            //                //                        leftPadding: 0
            //                //                        rightPadding: control.indicator.width + control.spacing

            //                rightPadding: 0
            //                leftPadding: control.indicator.width + control.spacing

            //                text: control.displayText
            //                font: control.font
            //                color: control.pressed ? headerColor : headerColor
            //                horizontalAlignment: Text.AlignLeft
            //                verticalAlignment: Text.AlignVCenter
            //                elide: Text.ElideRight
            //            }

            //            background: Rectangle
            //            {
            //                implicitWidth: 120
            //                implicitHeight: 30
            //                color: backgroundColor
            //                border.color: control.pressed ? headerColor : headerColor
            //                border.width: control.visualFocus ? 2 : 1
            //                radius: 2
            //            }

            //            popup: Popup {
            //                y: control.height //- 1
            //                width: control.width
            //                implicitHeight: listview.contentHeight
            //                padding: 1

            //                contentItem: ListView {
            //                    id: listview
            //                    clip: true
            //                    model: control.popup.visible ? control.delegateModel : null
            //                    currentIndex: control.highlightedIndex

            //                    ScrollIndicator.vertical: ScrollIndicator { }
            //                }

            //                background: Rectangle {
            //                    border.color: headerColor
            //                    radius: 2
            //                }
            //}
        }

        ChartView
        {
            Layout.alignment: Qt.AlignBottom
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.topMargin: 100
            Layout.bottomMargin: 100
            id: chart_view_cam
            //antialiasing: true
            margins { top: 0; bottom: 0; left: 0; right: 0 }
            legend.visible: false
            animationOptions: ChartView.NoAnimation
            backgroundColor: "transparent"

            ValueAxis
            {
                id: axis_y
                min: 0
                max: 1
                gridVisible: false
                color: "#ffffff"
                visible: false
            }

            ValueAxis
            {
                id: axis_x
                min: 0
                max: testis.axisXCount
                gridVisible: false
                color: "#ffffff"
                labelsColor: "#ffffff"
                labelFormat: "%.0f"
                visible: false

            }

            LineSeries
            {
                id: line_series_crank
                name: "Crank"
                color: crankGraphColor
                axisX: axis_x
                axisY: axis_y
                width: 4
                style: Qt.SolidLine
            }

            LineSeries
            {
                id: line_series_cam
                name: "Cam"
                color: camGraphColor
                axisX: axis_x
                axisY: axis_y
                width: 4
                style: Qt.SolidLine
                //visible: false

            }

            Connections
            {
                target: testis
                onUpdatePending:
                {
                    testis.updateCrankSamples(line_series_crank);
                    testis.updateCamSamples(line_series_cam);
                }
            }
        }
    }
}
