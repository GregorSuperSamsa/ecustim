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
        anchors.rightMargin: 10

        RowLayout
        {
            id: rowLayout
            Layout.alignment: Qt.AlignTop
            Layout.fillWidth: true
            spacing: 9

            RadioButton
            {
                id: radioButtonBluetooth
                //Layout.fillWidth: true
                Layout.preferredWidth: implicitWidth
                Layout.preferredHeight: implicitHeight
                text: qsTr("Bluetooth")
                checked: communicationManager.connectionType === CommunicationManager.BLUETOOTH
                onClicked:
                {
                    list.clearSelection()
                    communicationManager.setConnectionType(CommunicationManager.BLUETOOTH);
                }
            }

            RadioButton
            {
                id: radioButtonUsbUart
                //Layout.fillWidth: true
                Layout.preferredWidth: implicitWidth
                Layout.preferredHeight: implicitHeight
                text: qsTr("USB UART")
                checked: communicationManager.connectionType === CommunicationManager.USB_UART
                onClicked:
                {
                    list.clearSelection()
                    communicationManager.setConnectionType(CommunicationManager.USB_UART);
                }
            }

            Item
            {
                Layout.fillWidth: true

            }
        }

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

        BusyIndicator
        {
            id: busy
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.preferredWidth: implicitWidth
            Layout.preferredHeight: running ? implicitHeight : 0
            running: (communicationManager.connectionStatus === CommunicationManager.DISCOVERY_STARTED)
        }

        RowLayout
        {
            Layout.alignment: Qt.AlignHCenter | Qt.AlignBottom
            Layout.fillWidth: true
            Layout.preferredHeight:  contentItem.implicitHeight

            Button
            {
                id: buttonFind
                Layout.fillWidth: true
                Layout.preferredHeight: implicitHeight
                text: "Find"
                onClicked:
                {
                    list.clearSelection()
                    communicationManager.findDevices()
                }
            }

            Button
            {
                Layout.fillWidth: true
                Layout.preferredHeight: implicitHeight
                id: buttonConnect
                text: "Connect"
                onClicked:
                    communicationManager.connect(remoteDeviceDelegate.connectionString)
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
        onConnectionStatusChanged:
        {
           //
        }
    }
}
