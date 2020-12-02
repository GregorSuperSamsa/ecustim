import QtQuick 2.6
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0
import QtQuick.Controls.Material 2.3
import CommunicationManager 1.0


Item
{
    id: root
    ColumnLayout
    {
        anchors.fill: parent
        anchors.leftMargin: 10
        anchors.rightMargin:  10
        anchors.bottomMargin: 10
        spacing: 0

        ListView
        {
            id: list
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 10

            clip:true
            flickableDirection: Flickable.VerticalFlick
            boundsBehavior: Flickable.StopAtBounds
            ScrollBar.vertical: ScrollBar {}

            model: remoteDeviceDelegate

            function clearSelection()
            {
                remoteDeviceDelegate.selectedIndex = -1;
            }
        }


        RowLayout
        {
            id: rowLayout

            //Layout.alignment: Qt.AlignHCenter
            Layout.preferredHeight: implicitHeight
            Layout.fillWidth: true

            spacing: 0

//            Label {
//                Layout.preferredWidth: implicitWidth
//                Layout.preferredHeight: implicitHeight
//                id: connectionTypeLabel
//                text: qsTr("Connection type")
//            }

            RadioButton
            {
                id: radioButtonUsbUart
                Layout.preferredWidth: implicitWidth
                Layout.preferredHeight: implicitHeight
                text: qsTr("USB")
                checked: communicationManager.connectionType === CommunicationManager.USB_UART
                onClicked: {
                    communicationManager.setConnectionType(CommunicationManager.USB_UART);
                }
            }

            RadioButton
            {
                id: radioButtonBluetooth
                Layout.preferredWidth: implicitWidth
                Layout.preferredHeight: implicitHeight
                text: qsTr("Bluetooth")
                checked: communicationManager.connectionType === CommunicationManager.BLUETOOTH
                onClicked: {
                    communicationManager.setConnectionType(CommunicationManager.BLUETOOTH);
                }
            }
        }

        Button
        {
            id: buttonStartStopDiscovery

            property string startDiscoveryText: "Start discovery"
            property string stopDiscoveryText:  "Stop discovery"
            property bool startDiscovery : true

            Layout.fillWidth: true

            text: startDiscovery ? startDiscoveryText : stopDiscoveryText
            onClicked:
            {
                if (startDiscovery)
                {
                    list.clearSelection();
                    communicationManager.disconnect();
                    communicationManager.startRemoteDeviceDiscovery();
                }
                else
                {
                    communicationManager.stopRemoteDeviceDiscovery();
                }
                startDiscovery = !startDiscovery;
            }

        }
    }

    RemoteDeviceDelegate
    {
        id: remoteDeviceDelegate
    }

    Connections
    {
        target: communicationManager
        onRemoteDeviceDiscoveryFinished: {
            buttonStartStopDiscovery.startDiscovery = true;
        }
    }
}
