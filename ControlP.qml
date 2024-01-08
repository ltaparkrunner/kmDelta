import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
//import QtQuick.Controls.Styles 1.0
//import QtQuick.Dialogs 1.0

Rectangle{

    color: 'blue'

    Connections {
        target: controlIp // Указываем целевое соединение
        /* Объявляем и реализуем функцию, как параметр
         * объекта и с имененем похожим на название сигнала
         * Разница в том, что добавляем в начале on и далее пишем
         * с заглавной буквы
         * */
        function onSendToQml(count) {
            bottomText1.text = count // Устанавливаем счётчик в текстовый лейбл
        }
    }

    Text{
        id: uppText
        x: 10
        y: 10
        text: 'Com1'
    }
    Button{
        id : butt1
        x: uppText.x;
        y: uppText.y + uppText.height + 10
        text: "Choose COM"
    }
    Button{
        id : butt2
        x: uppText.x;
        y: butt1.y + butt1.height + 10
        text: "Start Test"
        onClicked: {
            controlIp.receiveFromQml()
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
        x: uppText.x;
        y: butt2.y + butt2.height + 10
        text: '00:00:00'
    }
    Text{
        id: bottomText2
        x: uppText.x;
        y: bottomText1.y + bottomText1.height + 10
        text: '00'
    }
    IP_Addr{
        anchors.top: bottomText2.bottom
        anchors.topMargin: 20
        Layout.fillWidth: true

    }
}
