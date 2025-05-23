import QtQuick 2.0

Rectangle{

    height:80
    Connections {
        target: vmConfigsChat
        function onSendToMB(title, text) {
            bottomText3.text = title
            bottomText4.text = text // Устанавливаем счётчик в текстовый лейбл
        }
    }
    Text{
        id: bottomText3
        x: 10;
        y: 10
        text: 'Источник сообщений'
    }
    Text{
        id: bottomText4
        x: bottomText3.x;
        y: bottomText3.y + bottomText3.height + 10
        text: 'Сообщение'
    }
}
