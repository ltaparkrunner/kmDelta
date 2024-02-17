import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.1

Rectangle{
    id:c_ip2
    width: ip_2.width
    color: 'blue'

    Connections {
        target: vmConfigs // Указываем целевое соединение
        /* Объявляем и реализуем функцию, как параметр
         * объекта и с имененем похожим на название сигнала
         * Разница в том, что добавляем в начале on и далее пишем
         * с заглавной буквы
         * */
//        function onSendToQml(count) {
          onSendToQml: {
            bottomText1.text = count // Устанавливаем счётчик в текстовый лейбл
        }
    }
    MessageDialog{
        id: messageDialog
        title: qsTr("May I have your attention, please?")
        text: qsTr("The document has been modified.")
        standardButtons: StandardButton.Ok //| StandardButton.Cancel
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
    }
    Button{
        id : connectButt
        text: "Connect"
        onClicked: {
            vmConfigs.connectButt(ip_2.ip_t, ip_2.port_t)
            messageDialog.open()
        }
    }
    Button{
        id : sendMessButt
        text: "Request params"
        onClicked: {
            vmConfigs.getParamsButt(ip_2.ip_t, ip_2.port_t)
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
    }
    RowLayout{
        Button{
            id : periodicRequestButt
            text: "Periodic request"
            onClicked: {
                vmConfigs.periodReqButt(ip_2.ip_t, ip_2.port_t, 3000)
            }
        }
    }
    }
}
