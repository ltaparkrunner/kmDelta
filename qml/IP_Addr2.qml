import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtCharts 2.0
//import QtQuick.Controls 1.0
import QtQuick.Controls //2.0     //1.0 //2.0
import QtQuick.Dialogs  //1.2 //2.0     //1.2

Rectangle {
    id: ip_contain
    width: 384
    //height: 200
    property int ht: 400    //310//500
    property string ip_t: ip.text
    property string port_t: port.text
//    property int ip_w: Math.max(t1.width, t2.width, t3.width) + rect_2 *2
//    height: 2000
    readonly property int butth: 40//50
    readonly property int tinph: 25
    readonly property int spch:  20  //10     // 5     //10

//    readonly property font myFont: ({
//            family: "Helvetica",
////            pointSize: 20,
//            pixelSize: 17,
//            bold: false     //true
//        })
    function getParams(ls){
        ls[0] = ip.text;   //addrp;
        ls[2] = mask.text; //maskp;
        ls[4] = port.text;    //portp;
        ls[1] =  ip_2.text;
        ls[3] = mask_2.text;
        ls[5] = port_2.text;
    }

    function sendParams(){
        var sList = [" Forever For "];
//        sList.append(ip.text);
        sList.push(ip.text)
        sList.push(mask.text);
        sList.push(port.text);
        vmConfigsChat.loadDefaultButt(sList)
//        return(sList);
    }

    Connections{
        target: vmConfigsChat
        function onSendCurrIp(ls)
//        onSendCurrIp:
        {
           ip.text = ls[0];   //addrp;
           mask.text = ls[2]; //maskp;
           port.text = ls[4];    //portp;
           ip_2.text = ls[1];
           mask_2.text = ls[3];
           port_2.text = ls[5];
        }
        function onSendCurrIp_2(ls)
//        onSendCurrIp_2:
        {
            ip.text = ls;
        }
    }
    ColumnLayout{
        spacing: spch
        Layout.rightMargin: 20
//        Layout.topMargin: 10
        anchors.fill: parent

        RowLayout{
            Layout.alignment: Qt.AlignHCenter
            spacing: 10
//            Layout.margins: parent.Layout.margins
            Button{
                id : butt_load_file
//                text: "Load_From_File"
                text: "Загрузить из файла"
//                font: myFont
                onClicked: {
//                    vmConfigsChat.loadFileButt()
                    sendButt(8)
                }
                implicitHeight: butth
                implicitWidth: 172
            }
            Button{
                id : butt_save_file
//                text: "Save_To_File"
                text: "Сохранить настройки в файл"
//                font : myFont
                onClicked: {
//                    var ls = [];
//                    ls[0] = ip.text;   //addrp;
//                    ls[2] = mask.text; //maskp;
//                    ls[4] = port.text;    //portp;
//                    ls[1] =  ip_2.text;
//                    ls[3] = mask_2.text;
//                    ls[5] = port_2.text;
//                    vmConfigsChat.saveFileButt(ls)
                    sendButt(9)
                }
                implicitHeight: butth
                implicitWidth: 172
            }
        }
        RowLayout{
            Layout.alignment: Qt.AlignHCenter
            spacing: 10
            Button{
                id : butt_load_device
                height: butth
//                text: "Load_From_Device"
                text: "Загрузить из устройства"
//                font : myFont
                onClicked: {
//                    vmConfigsChat.loadDeviceButt()
//                    sendParams()
                      sendButt(7)
                    }
                implicitWidth: 172
                implicitHeight: butth
            }
            Button{
                id : butt_save_device
                height: butth
//                 text: "Save_To_Device"
                text: "Записать в устройство"
//                font : myFont
                onClicked: {
//                        var ls = [];
//                        ls[0] = ip.text;   //addrp;
//                        ls[2] = mask.text; //maskp;
//                        ls[4] = port.text;    //portp;
//                        ls[1] =  ip_2.text;
//                        ls[3] = mask_2.text;
//                        ls[5] = port_2.text;
////                        vmConfigsChat.saveDeviceButt(ls)
//                        vmConfigsChat.pushedButt(ls, 6)
                    sendButt(6)
                }
                implicitWidth: 172
                implicitHeight: butth
            }
        }
        Button{
            Layout.alignment: Qt.AlignHCenter
            id : butt_default
//            width: 640
            height: butth
//            text: "Load_Defaults"
            text: "Загрузить параметры по умолчанию в программу"
            onClicked: {
//                sendButt(7);
                sendButt(12)
                }
            implicitWidth: 354
            implicitHeight: butth
        }

        RowLayout{
            Layout.alignment: Qt.AlignHCenter
//            spacing: 5
            ColumnLayout{
                spacing: spch
                Layout.alignment: Qt.AlignTop
                Rectangle{
                    height: tinph
                    width: 100
//                    border{color: "black"}
                }
                Rectangle{
                    height: tinph
                    width: 100
                    Text {
                        id: t1
                        text: qsTr("IP-адрес")
    //                    font : myFont
                    }
                }
                Rectangle{
                    height: tinph
                    width: 100
                    Text {
                        id: t2
                        text: qsTr("IP-маска")
    //                    font : myFont
                    }
                }
                Rectangle{
                    height: tinph
                    width: 100
                    Text {
                        id: t3
                        text: qsTr("порт")
    //                    font : myFont
                    }
                }
            }
            ColumnLayout{
                spacing: spch
                Rectangle{
                    height: tinph - 10
                    width: 130
                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: qsTr("текущие")
    //                    font : myFont
                    }
                }
                Rectangle{
                    id: rect_2
                    height: tinph
                    width: 130
                    border{color: "black"}

//                    color: "yellow"
                    TextInput{
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        anchors.fill: parent
                        id: ip
                        text: /*vmConfigsChat.ip_n */ "forever"
                        font : myFont
                        //Binding{ target: vmConfigsChat; property: "ip_n"; value: ip.text }
                    }
                }
                Rectangle{
                    height: tinph
                    width: 130
//                    color: "yellow"
                    border{color: "black"}
                    TextInput{
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        anchors.fill: parent
                        id: mask
                        text: "forever"
                        font : myFont
                    }
                }
                Rectangle{
                    //anchors.leftMargin: 5
                    height: tinph
                    width: 130
//                    color: "yellow"
                    border{color: "black"}
                    TextInput{
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        anchors.fill: parent
                        id: port
                        text: "forever"
                        font : myFont
                    }
                }
            }
            ColumnLayout{
                spacing: spch
                Rectangle{
                    height: tinph - 10
                    width: 130
                        Text {
                            anchors.horizontalCenter: parent.horizontalCenter
                            text: qsTr("установить ")
                        }
                }
                Rectangle{
                    height: tinph
                    width: 130
//                    color: "yellow"
                    border{color: "black"}
                    TextInput{
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        anchors.fill: parent
                        id: ip_2
                        text: "forever"
                        font : myFont
                    }
                }
                Rectangle{
                    height: tinph
                    width: 130
//                    color: "yellow"
                    border{color: "black"}
                    TextInput{
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        anchors.fill: parent
                        id: mask_2
                        text: "forever"
                        font : myFont
                    }
                }
                Rectangle{
                    //anchors.leftMargin: 5
                    height: tinph
                    width: 130
//                    color: "yellow"
                    border{color: "black"}
                    TextInput{
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        anchors.fill: parent
                        id: port_2
                        text: "forever"
                        font : myFont
                    }
                }
            }
        }
        RowLayout{
            Layout.alignment: Qt.AlignHCenter
            spacing: 10
//            Layout.margins: 10
//            leftMargin: 10
//            rightMargin: 10
            Button{
                id : sendMesgButt
//                text: "Request params"
                text: "Считать параметры с устройства"
//                font : myFont
                onClicked: {
//                    vmConfigsChat.getParamsButt(ip_t, port_t)
                    sendButt(7)
                }
                implicitWidth: 172
                implicitHeight: butth
            }
            Button{
                id : butt_Commit
                width: 100
                height: butth
//                text: "Set params"
                text: "Установить параметры на устройство"
//                font : myFont
                onClicked: {
                    sendButt(6)
//                    var ls = [];
//                    ls[0] = ip.text;   //addrp;
//                    ls[2] = mask.text; //maskp;
//                    ls[4] = port.text;    //portp;
//                    ls[1] =  ip_2.text;
//                    ls[3] = mask_2.text;
//                    ls[5] = port_2.text;
////                    vmConfigsChat.setParamsButt(ls)
//                    vmConfigsChat.pushedButt(ls, 6)
                }
                implicitWidth: 172
                implicitHeight: butth
    //            implicitHeight: 20
            }
        }
    }
    function sendButt(n){
        var ls = [];
        ls[0] = ip.text;   //addrp;
        ls[2] = mask.text; //maskp;
        ls[4] = port.text;    //portp;
        ls[1] =  ip_2.text;
        ls[3] = mask_2.text;
        ls[5] = port_2.text;
//                    vmConfigsChat.setParamsButt(ls)
        vmConfigsChat.pushedButt(ls, n)
    }
}
