import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtCharts 2.0
//import QtQuick.Controls 1.0
import QtQuick.Controls 2.0


Rectangle {
    id: ip_contain
    width: 270
    //height: 200
    property int ht: 230
    property string ip_t: ip.text
    property string port_t: port.text
//    property int ip_w: Math.max(t1.width, t2.width, t3.width) + rect_2 *2
//    height: 2000

    function sendParams(){
        var sList = [" Forever For "];
//        sList.append(ip.text);
        sList.push(ip.text)
        sList.push(mask.text);
        sList.push(port.text);
        vmConfigsChat.load_Default_Qml(sList)
//        return(sList);
    }

    Connections{
        target: vmConfigsChat
//        function onSendToQml2(addrp, maskp, portp)
        onSendCurrIp:
        {
           ip.text = ls[0];   //addrp;
           mask.text = ls[2]; //maskp;
           port.text = ls[4];    //portp;
           ip_2.text = ls[1];
           mask_2.text = ls[3];
           port_2.text = ls[5];
        }
        onSendCurrIp_2:
        {
            ip.text = ls;
        }
    }
    ColumnLayout{
        spacing: 3
        anchors.fill: parent

        RowLayout{
            Button{
                id : butt_load_file
                width: 420
                height: 20
                text: "Load_From_File"
                onClicked: {
                    vmConfigsChat.load_File_Qml()
                    }
                implicitWidth: 107
            }
            Button{
                id : butt_save_file

                width: 1020
                height: 20
                text: "Save_To_File"
                onClicked: {
                    var ls = [];
                    ls[0] = ip.text;   //addrp;
                    ls[2] = mask.text; //maskp;
                    ls[4] = port.text;    //portp;
                    ls[1] =  ip_2.text;
                    ls[3] = mask_2.text;
                    ls[5] = port_2.text;
                    vmConfigsChat.save_File_Qml(ls)
                }
                implicitWidth: 107
            }
        }
        RowLayout{
            Button{
                id : butt_load_device
                width: 220
                height: 20
                text: "Load_From_Device"
                onClicked: {
                    vmConfigsChat.load_Device_Qml()
                    }
                implicitWidth: 107
            }
            Button{
                id : butt_save_device
                width: 220
                height: 20
                text: "Save_To_Device"
                onClicked: {
                    vmConfigsChat.save_Device_Qml()
                    }
                implicitWidth: 107
            }
        }
        Button{
            id : butt_default
            width: 640
            height: 20
            text: "Load_Defaults"
            onClicked: {
//                String t =
//                property var  str: ip.text
                sendParams();
//                vmConfigsChat.load_Default_Qml()
                }
            implicitWidth: 220
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
                        text: /*vmConfigsChat.ip_n */ "forever"
                        //Binding{ target: vmConfigsChat; property: "ip_n"; value: ip.text }
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
                vmConfigsChat.commitFromQml(ip.text)
            }
        }
    }
}
