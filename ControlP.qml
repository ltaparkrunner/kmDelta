import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
//import QtQuick.Controls.Styles 1.0
//import QtQuick.Dialogs 1.0

///import IP_Addr2.qml 1.0

Rectangle{
    id:c_ip2
    width: ip_2.width
    color: 'blue'

    Connections {
        target: controlIp // Указываем целевое соединение
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
ColumnLayout{
    spacing: 3
//    anchors.top: parent
//    anchors.left: parent
    Text{
        id: uppText
        //x: 10
//        y: 10
        text: 'Com1'
    }
    Button{
        id : butt1
        //x: uppText.x;
        //y: uppText.y + uppText.height + 10
        text: "Choose COM"
    }
    Button{
        id : connectButt
        //x: uppText.x;
        //y: butt1.y + butt1.height + 10
        text: "Connect"
        onClicked: {
            controlIp.connectButt(ip_2.ip_t, ip_2.port_t)
        }

    }
    Button{
        id : sendMessButt
        //x: uppText.x;
        //y: connectButt.y + connectButt.height + 10
        //y: connectButt.bottom + 10
        text: "Send Message"
        onClicked: {
            controlIp.sendMsgButt()
        }

    }

    /*
    Connections {
            target: butt1
            function onClicked() {
                controlP.receiveEromQML()
       }
    }
    */
    Text{
        id: bottomText1
        //x: uppText.x;
        //y: butt2.y + butt2.height + 10
//        anchors.top: sendMessButt.bottom + 10
        text: '00:00:00'
    }
    Text{
        id: bottomText2
        //x: uppText.x;
        //y: bottomText1.y + bottomText1.height + 10
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
                controlIp.periodReqButt(ip_2.ip_t, ip_2.port_t)
            }
        }
        Button{
            id : setParamButt
            text: "Set params"
            onClicked: {
                controlIp.setParamButt(ip_2.ip_t, ip_2.port_t)
            }
        }
    }
    }
}
