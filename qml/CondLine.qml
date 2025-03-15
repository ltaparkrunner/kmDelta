import QtQuick 2.0

Rectangle{

    height:80
    //color: 'green'
    readonly property font myFont: ({
            family: "Helvetica",
//            pointSize: 20,
            pixelSize: 20,
            bold: false //true
        })
    Connections {
        target: vmConfigsChat // Указываем целевое соединение
        /* Объявляем и реализуем функцию, как параметр
         * объекта и с имененем похожим на название сигнала
         * Разница в том, что добавляем в начале on и далее пишем
         * с заглавной буквы
         * */
        function onSendToMB(title, text) {
//          onSendToMB: {
            bottomText3.text = title // Устанавливаем счётчик в текстовый лейбл
            bottomText4.text = text // Устанавливаем счётчик в текстовый лейбл
        }
    }
    Text{
        id: bottomText3
        x: 10;
        y: 10
        text: '00:00:00'
//        font: myFont
    }
    Text{
        id: bottomText4
        x: bottomText3.x;
        y: bottomText3.y + bottomText3.height + 10
        text: '00'
//        font: myFont
    }
}
