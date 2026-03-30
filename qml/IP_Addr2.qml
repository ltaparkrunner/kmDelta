import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtCharts 2.0
import QtQuick.Controls
import QtQuick.Dialogs

Rectangle {
    id: ip_contain
    width: 384
    property int ht: 310
    property string ip_t: ip.text
    property string port_t: port.text
    readonly property int butth: 40//50
    readonly property int tinph: 25
    readonly property int spch:   5     //10

    readonly property font myFont: ({
            family: "Helvetica",
//            pointSize: 20,
            pixelSize: 14,
            bold: false     //true
        })
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
        sList.push(ip.text)
        sList.push(mask.text);
        sList.push(port.text);
        vmConfigsChat.loadDefaultButt(sList)
    }

    Connections{
        target: vmConfigsChat
        function onSendCurrIp(ls)
        {
           ip.text = ls[0];   //addrp;
           mask.text = ls[2]; //maskp;
           port.text = ls[4];    //portp;
           ip_2.text = ls[1];
           mask_2.text = ls[3];
           port_2.text = ls[5];
        }
        function onSendCurrIp_2(ls)
        {
            ip.text = ls;
        }
    }
    ColumnLayout{
        spacing: spch
        Layout.rightMargin: 20
        anchors.fill: parent

        RowLayout{
            Layout.alignment: Qt.AlignHCenter
            spacing: 10
            Button{
                id : butt_load_file
                text: "Загрузить настройки
   из файла"
//                font: myFont
                onClicked: {
                    sendButt(8)
                }
                implicitHeight: butth
                implicitWidth: 172
            }
            Button{
                id : butt_save_file
                text: "Сохранить настройки
     в файл"
//                font : myFont
                onClicked: {
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
                text: "Загрузить из устройства"
                font : myFont
                onClicked: {
                      sendButt(7)
                    }
                implicitWidth: 172
                implicitHeight: butth
            }
            Button{
                id : butt_save_device
                height: butth
                text: "Записать в устройство"
                font : myFont
                onClicked: {
                    sendButt(6)
                }
                implicitWidth: 172
                implicitHeight: butth
            }
        }
        Button{
            Layout.alignment: Qt.AlignHCenter
            id : butt_default
            height: butth
            text: "Загрузить параметры по умолчанию в программу"
            font : myFont
            onClicked: {
                sendButt(12)
                }
            implicitWidth: 354
            implicitHeight: butth
        }

        RowLayout{
            Layout.alignment: Qt.AlignHCenter
            ColumnLayout{
                spacing: spch
                Layout.alignment: Qt.AlignTop
                Rectangle{
                    height: tinph
                    width: 100
                }
                Rectangle{
                    height: tinph
                    width: 100
                    Text {
                        id: t1
                        text: qsTr("IP-адрес")
                        font : myFont
                    }
                }
                Rectangle{
                    height: tinph
                    width: 100
                    Text {
                        id: t2
                        text: qsTr("IP-маска")
                        font : myFont
                    }
                }
                Rectangle{
                    height: tinph
                    width: 100
                    Text {
                        id: t3
                        text: qsTr("порт")
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
                        text: qsTr("текущие")
                        font : myFont
                    }
                }
                Rectangle{
                    id: rect_2
                    height: tinph
                    width: 130
                    border{color: "black"}
                    TextInput{
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        anchors.fill: parent
                        id: ip
                        text: /*vmConfigsChat.ip_n */ "000.000.000.000"
                        font : myFont
                    }
                }
                Rectangle{
                    height: tinph
                    width: 130

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
                    height: tinph
                    width: 130
                    border{color: "black"}
                    TextInput{
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        anchors.fill: parent
                        id: port
                        text: "000.000.000.000"
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
                    height: tinph
                    width: 130
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

            Button{
                id : sendMesgButt
//                Rectangle {
                text: "Считать параметры
   с устройства"
//                font : myFont
//               }
                enabled: false
                onClicked: {
                    sendButt(7)
                }
                implicitWidth: 172
                implicitHeight: butth
            }
            Button{
                id : butt_Commit
                width: 100
                height: butth
                text: "Установить параметры
   на устройство"
//                font : myFont
                enabled: false
                onClicked: {
                    sendButt(6)
                }
                implicitWidth: 172
                implicitHeight: butth
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
        vmConfigsChat.pushedButt(ls, n)
    }
}
