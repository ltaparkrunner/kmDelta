import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtCharts 2.0
import QtQuick.Controls 1.0


Rectangle {
    id: ip_contain
    width: 270
    //height: 200
    property int ht: 200
    property string ip_t: ip.text
    property string port_t: port.text
//    property int ip_w: Math.max(t1.width, t2.width, t3.width) + rect_2 *2
//    height: 2000
    Connections{
        target: ipAddr
//        function onSendToQml2(addrp, maskp, portp)
        onSendToQml2:
        {
           ip.text = ip_addr;   //addrp;
           mask.text = ip_mask; //maskp;
           port.text = ip_port;    //portp;
        }
//        onRequestFromQml2:
//        {
//           r_ip = ip.text
//           r_mask = mask.text
//           r_port = port.text
//        }
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
            ColumnLayout{
                Text {
                    id: t1
                    text: qsTr("IP-адрес")
                }
                Text {
                    id: t2
                    text: qsTr("IP-маска")
                }
                Text {
                    id: t3
                    text: qsTr("порт")
                }
            }
            ColumnLayout{
                Text {
//                    Layout.leftMargin: 30
                    text: qsTr("текущие")
                }
                Rectangle{
                    id: rect_2
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
            ColumnLayout{
                Text {
    //                id: ip_a
//                    Layout.leftMargin: 20
                    text: qsTr("установить ")
                }
                Rectangle{
                    height: 20
                    width: 100
                    color: "yellow"
                    TextInput{
                        color: "green"
                        anchors.fill: parent
                        id: ip_2
                        text: "forever"
                    }
                }
                Rectangle{
                    height: 20
                    width: 100
                    color: "yellow"
                    TextInput{
                        color: "green"
                        anchors.fill: parent
                        id: mask_2
                        text: "forever"
                    }
                }
                Rectangle{
                    //anchors.leftMargin: 5
                    height: 20
                    width: 100
                    color: "yellow"
                    TextInput{
                        color: "green"
                        anchors.fill: parent
                        id: port_2
                        text: "forever"
                    }
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
