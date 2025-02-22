import QtQuick 2.0
//import QtQuick.Controls 1.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
//import QtQuick.Dialogs 1.0
import QtQuick.Dialogs //1.2  //2.0       // TODO strange it works without version???

Rectangle{
    id:c_ip2
    width: ip_2.width
    color: 'blue'

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
    }
    MessageDialog{
        id: messageDialog
        title: qsTr("May I have your attention, please?")
        text: qsTr("The document has been modified.")
        //standardButtons: StandardButton.Ok //| StandardButton.Cancel
//        buttons: MessageDialog.Ok
    }

ColumnLayout{
    spacing: 3
    Text{
        id: uppText
        text: 'Com1'
    }
    Button{
        id : butt1
        text: "Choose COM"
        implicitWidth: 107
    }
    RowLayout{
        Button{
            id : connectButt
            width : 220
            text: "Connect"
            onClicked: {
                vmConfigsChat.connectButt(ip_2.ip_t, ip_2.port_t)
    //            messageDialog.open()
            }
            implicitWidth: 107
        }
        Button{
            id : disconnectButt
            width : 220
            text: "Disconnect"
            onClicked: {
                vmConfigsChat.disconnectButt(ip_2.ip_t, ip_2.port_t)
    //            messageDialog.open()
            }
            implicitWidth: 107
        }
    }
    Text{
        id: bottomText1
        text: '00:00:00'
    }
    Text{
        id: bottomText2
        text: '00'
    }
     IP_Addr2{
        id: ip_2
        color: parent.parent.color
        Layout.preferredHeight: ip_2.ht
        implicitHeight: 207
    }
    RowLayout{
        Button{
            id : periodicRequestButt
            width : 220
            text: "Periodic request"
            onClicked: {
                vmConfigsChat.periodReqButt(ip_2.ip_t, ip_2.port_t, 3000)
            }
            implicitWidth: 107
        }
        Button{
            id : stopRequestButt
            width : 220
            text: "Stop request"
            onClicked: {
                vmConfigsChat.stopReqButt(ip_2.ip_t, ip_2.port_t, 3000)
            }
            implicitWidth: 107
        }
    }
    Button{
        id : setTimeButt
        width : 220
        text: "Set Date Time"
        onClicked: {
            vmConfigsChat.setTimeButt(ip_2.ip_t, ip_2.port_t, 3000)
        }
        implicitWidth: 220
    }
    }
}
