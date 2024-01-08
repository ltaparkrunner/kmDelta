import QtQuick 2.0

Rectangle{
    //Layout.maximumHeight: 480//parent.height
    //Layout.maximumWidth: 640//parent.width
    //width: main1.width
    //height: main1.height/2
    //x:
    //y: upp1.bottom
    //bottom: main1.bottom

    Connections {
        target: mbtcpClient // Указываем целевое соединение
        /* Объявляем и реализуем функцию, как параметр
         * объекта и с имененем похожим на название сигнала
         * Разница в том, что добавляем в начале on и далее пишем
         * с заглавной буквы
         * */
        function onSendToCond1(str, bl) {
            bottomText3.text = str // Устанавливаем счётчик в текстовый лейбл
            if(bl === true) bottomText4.text = "together";
            else bottomText4.text = "forever";
        }
        function onSendToCond2(str1, str2) {
            bottomText3.text = str1 // Устанавливаем счётчик в текстовый лейбл
            bottomText4.text = str2
        }
    }
    color: 'green'
    Text{
        id: bottomText3
        x: 10;
        y: 10
        text: '00:00:00'
    }
    Text{
        id: bottomText4
        x: bottomText3.x;
        y: bottomText3.y + bottomText3.height + 10
        text: '00'
    }
}
