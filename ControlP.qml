import QtQuick 2.0
//import QtQuick.Controls 1.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
//import QtQuick.Dialogs 1.0
import QtQuick.Dialogs //2.0       // TODO strange it works without version???

Rectangle{
    readonly property font myFont: ({
            family: "Helvetica",
//            pointSize: 20,
            pixelSize: 17,
            bold: false //true
        })
    readonly property int butth: 40
    readonly property int spch: 20
    id:c_ip2
    width: ipAddr_2.width
    //color: 'white'
    Layout.margins: 10
    Connections {
        target: vmConfigsChat // Указываем целевое соединение
        /* Объявляем и реализуем функцию, как параметр
         * объекта и с имененем похожим на название сигнала
         * Разница в том, что добавляем в начале on и далее пишем
         * с заглавной буквы
         * */
        function onSendToQml(count) {
//          onSendToQml: {
            bottomText1.text = count // Устанавливаем счётчик в текстовый лейбл
        }
        function onSendTimeDate(d, t) {
            bottomText1.text = d;
            bottomText2.text = t;
        }
    }
    MessageDialog{
        id: messageDialog
        title: qsTr("May I have your attention, please?")
        text: qsTr("The document has been modified.")
        //standardButtons: StandardButton.Ok //| StandardButton.Cancel
//        buttons: MessageDialog.Ok
    }

ColumnLayout{
    spacing: spch
//    anchors.horizontalCenter: parent.horizontalCenter
    Text{
        Layout.alignment: Qt.AlignHCenter
        id: uppText
//        text: 'Device Date Time'
        text: 'Дата, Время Устройства'
//        font: myFont
    }
//    Button{
//        id : butt1
//        text: "Choose COM"
//        implicitWidth: 107
//    }
    RowLayout{
//        anchors.horizontalCenter: parent.horizontalCenter
        Layout.alignment: Qt.AlignHCenter
        spacing: 10
//        Layout.margins: 10
        Text{
            id: bottomText1
            text: '00:00:00'
//            font: myFont
        }
        Text{
            id: bottomText2
            text: '00'
//            font: myFont
        }
    }
    RowLayout{
        spacing: 10
//        anchors.horizontalCenter: parent.horizontalCenter
        Layout.alignment: Qt.AlignHCenter
        Button{
            id : connectButt
//            width : 220
//            text: "Connect"
            text: qsTr("Соединить")
//            font: myFont
            onClicked: {
                vmConfigsChat.connectButt(ip_2.ip_t, ip_2.port_t)
    //            messageDialog.open()
                sendButt(1)
            }
            implicitWidth: 172
            implicitHeight: butth
        }
        Button{
            id : disconnectButt
//            width : 220
//            text: "Disconnect"
            text: qsTr("Разъединить")
//            font: myFont
            onClicked: {
                sendButt(2)
//                vmConfigsChat.disconnectButt(ipAddr_2.ip_t, ipAddr_2.port_t)
    //            messageDialog.open()
            }
            implicitWidth: 172
            implicitHeight: butth
        }
    }

     IP_Addr2{
        id: ipAddr_2
        color: parent.parent.color
        Layout.preferredHeight: ipAddr_2.ht
//        implicitHeight: 400     //217
    }
    RowLayout{
        spacing: 10
//        Layout.margins: 10
//        anchors.horizontalCenter: parent.horizontalCenter
        Layout.alignment: Qt.AlignHCenter
        Button{
            id : periodicRequestButt
//            text: "Periodic request"
            text: "Опрос датчиков"
//            font: myFont
            onClicked: {
                vmConfigsChat.periodReqButt(ip_2.ip_t, ip_2.port_t, 3000)
            }
            implicitWidth: 172
            implicitHeight: butth
        }
        Button{
            id : stopRequestButt
//            text: "Stop request"
            text: "Остановить опрос датчиков"
//            font: myFont
            onClicked: {
                vmConfigsChat.stopReqButt(ip_2.ip_t, ip_2.port_t, 3000)
            }
            implicitWidth: 172
            implicitHeight: butth
        }
    }
    Button{
        Layout.alignment: Qt.AlignHCenter
        id : setTimeButt
//        text: "Set Date Time"
        text: qsTr("Установить Дату и Время")
//        font: myFont
        onClicked: {
            sendButt(5)
//            vmConfigsChat.setTimeButt(ipAddr_2.ip_t, ipAddr_2.port_t, 3000)
        }
        implicitWidth: 354
        implicitHeight: butth
    }
    }
    function sendButt(n){
        var ls = [];
        ipAddr_2.getParams(ls)
        vmConfigsChat.pushedButt(ls, n)
}
}
