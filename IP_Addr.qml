import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtCharts 2.0
import QtQuick.Controls 1.0

Rectangle {
    Connections{
        target: ipAddr
//        function onSendToQml2(addrp, maskp, portp)
        onSendToQml2:
        {
           ip.text = ip_addr;   //addrp;
           mask.text = ip_mask; //maskp;
           port.text = ip_port;    //portp;
        }
    }

    ColumnLayout{
        spacing: 3
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
                Layout.leftMargin: 30
                text: qsTr("текущие")
            }
            Text {
//                id: ip_a
                Layout.leftMargin: 20
                text: qsTr("установить ")
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
