import QtQuick 2.6
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0
import QtQuick.Controls.Material 2.3
import Communication 1.0


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
            Layout.preferredHeight: contentItem.implicitHeight
            spacing: 9

            RadioButton
            {
                id: radioButtonBluetooth
                Layout.fillWidth: true
                Layout.preferredWidth: 1
                Layout.preferredHeight: implicitHeight
                text: qsTr("Bluetooth")
                onClicked:
                    communicator.setConnectionType(Communication.BLUETOOTH);

            }

            RadioButton
            {
                id: radioButtonUsbUart
                Layout.fillWidth: true
                Layout.preferredWidth: 1
                Layout.preferredHeight: implicitHeight
                text: qsTr("USB UART")
                onClicked:
                    communicator.setConnectionType(Communication.USB_UART);
            }

            Item
            {
                Layout.fillWidth: true
                Layout.preferredWidth: 2
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

            model:  getDelegateModel()
            function getDelegateModel()
            {
                switch(communicator.connectionType)
                {
                case Communication.BLUETOOTH:
                    return bluetoothDelegateModel;
                case Communication.USB_UART:
                    return usbUartDelegateModel;
                case Communication.UNKNOWN:
                    return 0
                }
            }
        }

        RowLayout
        {
            Layout.alignment: Qt.AlignHCenter | Qt.AlignBottom
            Layout.fillWidth: true
            Layout.preferredHeight: contentItem.implicitHeight

            Button
            {
                id: buttonFind
                Layout.fillWidth: true
                Layout.preferredHeight: implicitHeight
                text: "Find"
                onClicked:
                    communicator.findDevices(communicator.connectionType)
            }

            Button
            {
                Layout.fillWidth: true
                Layout.preferredHeight: implicitHeight
                id: buttonConnect
                text: "Connect"
            }
        }
    }

    UsbUartDelegateModel
    {
        id: usbUartDelegateModel
        onSelectedIndexChanged:
        {
            list.currentIndex = selectedIndex
            console.log("List uart current index = " + list.currentIndex)

        }
    }

    BluetoothDelegateModel
    {
        id: bluetoothDelegateModel
        onSelectedIndexChanged:
        {
            list.currentIndex = selectedIndex
            console.log("List bt current index = " + list.currentIndex)
        }
    }
}
