import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import QtQuick.Dialogs        // TODO strange it works without version???

Rectangle{
    readonly property font myFont: ({
            family: "Helvetica",
            pixelSize: 14,
            bold: false //true
        })
    readonly property int butth: 40
    readonly property int spch: 7
    id:c_ip2
    width: ipAddr_2.width
    //color: 'white'
    Layout.margins: 10
    Connections {
        target: vmConfigsChat
        function onSendToQml(count) {
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
    }

ColumnLayout{
    spacing: spch
    Text{
        Layout.alignment: Qt.AlignHCenter
        id: uppText
        text: 'Дата, Время Устройства'
        font: myFont
    }
    RowLayout{
        Layout.alignment: Qt.AlignHCenter
        spacing: 10
        Text{
            id: bottomText1
            text: '01-01-2000'
            font: myFont
        }
        Text{
            id: bottomText2
            text: '01:01:01'
            font: myFont
        }
    }
    RowLayout{
        spacing: 10
        Layout.alignment: Qt.AlignHCenter
        Button{
            id : connectButt
            text: qsTr("Соединить")
            font: myFont
            onClicked: {

                sendButt(1)
            }
            implicitWidth: 172
            implicitHeight: butth
        }
        Button{
            id : disconnectButt
            text: qsTr("Разъединить")
            font: myFont
            onClicked: {
                sendButt(2)
            }
            implicitWidth: 172
            implicitHeight: butth
        }
    }

     IP_Addr2{
        id: ipAddr_2
        color: parent.parent.color
        Layout.preferredHeight: ipAddr_2.ht
    }
    RowLayout{
        spacing: 10
        Layout.alignment: Qt.AlignHCenter
        Button{
            id : periodicRequestButt
            text: "Опрос датчиков"
            font: myFont
            onClicked: {
                sendButt(3)
            }
            implicitWidth: 172
            implicitHeight: butth
        }
        Button{
            id : stopRequestButt
            text: "Остановить опрос" //" датчиков"
            font: myFont
            onClicked: {
                sendButt(4)
            }
            implicitWidth: 172
            implicitHeight: butth
        }
    }
    Button{
        Layout.alignment: Qt.AlignHCenter
        id : setTimeButt
        text: qsTr("Установить Дату и Время")
        font: myFont
        onClicked: {
            sendButt(5)
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
