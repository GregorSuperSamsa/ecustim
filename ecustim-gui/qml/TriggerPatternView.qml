import QtQuick 2.12
import QtCharts 2.1
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0
import QtQuick.Controls.Material 2.3

Item
{
    id: root

    ColumnLayout {
        anchors.fill: parent
        anchors.leftMargin: 10
        anchors.rightMargin:  10
        anchors.bottomMargin: 10
        spacing: 0

        ComboBox {
            id: combo
            Layout.fillWidth: true
            Layout.preferredHeight: implicitHeight
            model: hardwareManager.triggerPatternModel

            Material.elevation: 1

            property var triggerData: []
            delegate: ItemDelegate
            {
                id: control
                width: combo.width
                text: item.description
                highlighted: (combo.currentIndex === index)


                onClicked: {
                    combo.displayText = "Trigger pattern  [ " + text + " ]"

                    combo.triggerData = item.data

                    crankWheelCanvas.requestPaint();
                    crankPlotCanvas.requestPaint();

                    camWheelCanvas.requestPaint();
                    camPlotCanvas.requestPaint();
                }
            }
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredHeight: 3

            ColumnLayout
            {
                Layout.fillHeight: true
                Layout.fillWidth: true

                Label {
                    Layout.fillWidth: true
                    horizontalAlignment: Qt.AlignHCenter
                    verticalAlignment: Qt.AlignVCenter
                    text: "CRANKSHAFT"
                    Layout.topMargin: 5
                    Layout.bottomMargin: 5
                }

                Canvas {
                    id: crankWheelCanvas
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    clip: true
                    onPaint: {
                        drawTriggerWheel(
                                    getContext("2d"),
                                    width,
                                    height,
                                    combo.triggerData,
                                    "crank"
                                    );
                    }
                }
            }
            ColumnLayout
            {
                Layout.fillHeight: true
                Layout.fillWidth: true

                Label {
                    Layout.fillWidth: true
                    horizontalAlignment: Qt.AlignHCenter
                    verticalAlignment: Qt.AlignVCenter
                    text: "CAMSHAFT"
                    Layout.topMargin: 5
                    Layout.bottomMargin: 5
                }

                Canvas {
                    id: camWheelCanvas
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    clip: true
                    onPaint: {
                        drawTriggerWheel(
                                    getContext("2d"),
                                    width,
                                    height,
                                    combo.triggerData,
                                    "cam"
                                    );
                    }
                }
            }
        }




        Canvas {
            id: crankPlotCanvas
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredHeight: 1
            //Layout.topMargin: 3
            clip: true
            onPaint: {
                plotPattern(
                            getContext("2d"),
                            width,
                            height - 3,
                            combo.triggerData,
                            "crank"
                            );
            }
        }


        Canvas {
            id: camPlotCanvas
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredHeight: 1

            clip: true
            onPaint: {
                plotPattern(
                            getContext("2d"),
                            width,
                            height - 3,
                            combo.triggerData,
                            "cam"
                            );
            }
        }
    }

    // gearWheelType = "crank" | "cam"
    function plotPattern(context, width, height, data, wheelType)
    {
        context.reset();
        context.lineWidth = 2;

        var pulseWidth = width / data.length;
        var y = height
        var x = 0;

        let lastHigh = false
        let nextHigh = false
        context.beginPath();
        for(let i = 0; i < data.length; ++i++)
        {
            let high = (wheelType === "crank") ? (data[i] & 0x01) :  ((data[i] >> 1) & 0x01);

            if ((i + 1) < data.length) {
                nextHigh = (wheelType === "crank") ? (data[i+1] & 0x01) : ((data[i + 1] >> 1) & 0x01);
            }

            if (i === 0) {
                context.moveTo(x, y);
            }

            if (high)
            {
                if (!lastHigh) {
                    context.lineTo(x, y - y);

                }

                context.lineTo(x + pulseWidth, y - y);

                if (!nextHigh) {
                    context.lineTo(x + pulseWidth, y)
                }
            }
            else {
                context.lineTo(x + pulseWidth, y)
            }

            x += pulseWidth
            lastHigh = high
        }
        //context.closePath();
        context.strokeStyle = (wheelType === "crank") ? Material.accent : Material.color(Material.Teal)
        context.stroke();
    }

    // gearWheelType = "crank" | "cam"
    function drawTriggerWheel(context, width, height, data, wheelType)
    {
        context.reset();
        context.lineWidth = 2;

        // Center of trigger wheel
        var centerX = width / 2
        var centerY = height / 2;

        // Radius of the trigger wheel. By default crank wheel is drawn bigger than cam wheel
        var radius = (Math.min(width, height) / 2) * 0.8

        // Count of tooths, either low or high
        var arcsCount = data.length;

        if (wheelType === "crank") {
            radius =  Math.min(width, height) / 2;
            //
            for (var i = 0; i < data.length; ++i) {
                // If there is a tooth on the cam wheel,
                // available trigger data is represented 720 rotation degrees,
                // so crank tooths should be devided by 2 (360 rotation degrees)
                if (data[i] > 1) {
                    arcsCount = arcsCount / 2;
                    break;
                }
            }
        }

        // Degrees per single edge/arc
        var arcDegrees =  360 / arcsCount

        // Radians per single edge
        var arcRadians = arcDegrees * (Math.PI/180);

        //********* Draw the Trigger Wheel *********//
        // Start & end points of an arc in radians
        var arcStart = 0;
        var arcEnd = arcRadians;

        context.beginPath();
        for (let i = 0; i < arcsCount; i++)
        {
            let high = (wheelType === "crank") ? (data[i] & 0x01) :  ((data[i] >> 1) & 0x01);

            if (high) {
                context.arc(centerX, centerY, radius, arcStart + (arcRadians * 0.1), arcEnd - (arcRadians * 0.1), false);
            }
            else {
                context.arc(centerX, centerY, radius * 0.89, arcStart, arcEnd, false);
            }

            arcStart += arcRadians;
            arcEnd   += arcRadians;
        }
        context.closePath();
        context.strokeStyle = (wheelType === "crank") ? Material.accent : Material.color(Material.Teal)
        context.stroke();

        // Fill with semi-transparent color
        context.globalAlpha = 0.3;
        context.fillStyle = (wheelType === "crank") ? Material.accent : Material.color(Material.Teal)
        context.fill();
        context.globalAlpha = 1;

        if (arcsCount > 0) {
            // Cut out space for trigger wheel center hole
            context.globalCompositeOperation = 'destination-out';
            context.beginPath();
            context.arc(centerX, centerY, radius * 0.15, 0, 2 * Math.PI, false);
            context.closePath();
            context.fill();
            context.globalCompositeOperation = 'source-over';

            // Draw trigger wheel center hole
            context.beginPath();
            context.arc(centerX, centerY, radius * 0.15, 0, 2 * Math.PI, false);
            context.closePath();
            context.strokeStyle = (wheelType === "crank") ? Material.accent : Material.color(Material.Teal)
            context.stroke();
        }
    }
}
