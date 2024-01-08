import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtCharts 2.0
import QtQuick.Controls 1.0

Rectangle {
    Connections{
        target: ipAddr
        function onSendToQml2(addrp, maskp, portp)
        {
           ip.text = addrp;
           mask.text = maskp;
           port.text = portp;
        }
    }

    ColumnLayout{
        spacing: 2
        anchors.fill: parent
        Button{
            id : butt_ip
            width: 100
            height: 20
            text: "Load_IP"
            onClicked: {
                ipAddr.receiveFromQml()
                }
        }

        RowLayout{
            spacing: 8
            //anchors.fill: parent
            Text {
                id: ip_a
                text: qsTr("IP-адрес")
            }
            Rectangle{
                height: 20
                width: 100
                color: "yellow"
                TextInput{
                    color: "green"
                    anchors.fill: parent
                    id: ip
                    text: "forever"
                }
            }
        }
        RowLayout{
            spacing: 8
            //anchors.fill: parent
            Text {
                id: mask_a
                text: qsTr("IP-адрес")
            }
            Rectangle{
                height: 20
                width: 100
                color: "yellow"
                TextInput{
                    color: "green"
                    anchors.fill: parent
                    id: mask
                    text: "forever"
                }
            }
        }
        RowLayout{
            spacing: 8
            //anchors.fill: parent
            //spacing: 5
            Text {
                id: port_a
                text: qsTr("IP-адрес")
            }
            Rectangle{
                //anchors.leftMargin: 5
                height: 20
                width: 100
                color: "yellow"
                TextInput{
                    color: "green"
                    anchors.fill: parent
                    id: port
                    text: "forever"
                }
            }
        }
        Button{
            id : butt_Commit
            width: 100
            height: 20
            text: "Установить"
            onClicked: {
                ipAddr.commitFromQml(ip.text)
                }
        }
    }
}
