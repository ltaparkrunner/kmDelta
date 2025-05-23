import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.2       // TODO strange it works without version???

Rectangle{
//    readonly property font myFont: ({
//            family: "Helvetica",
////            pointSize: 20,
//            pixelSize: 17,
//            bold: false //true
//        })
    readonly property font myFont:("Helvetica")
    readonly property int butth: 40
    readonly property int spch: 7
    id:c_ip2
    width: ipAddr_2.width
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
    }
    RowLayout{
        Layout.alignment: Qt.AlignHCenter
        spacing: 10
        Text{
            id: bottomText1
            text: '01-01-2000'
        }
        Text{
            id: bottomText2
            text: '01:01:01'
        }
    }
    RowLayout{
        spacing: 10
        Layout.alignment: Qt.AlignHCenter
        Button{
            id : connectButt
            text: qsTr("Соединить")
            onClicked: {
                sendButt(1)
            }
            implicitWidth: 172
            implicitHeight: butth
        }
        Button{
            id : disconnectButt
            text: qsTr("Разъединить")
            onClicked: {
                sendButt(2)
            }
            implicitWidth: 172
            implicitHeight: butth
        }
    }

     IP_Addr_5{
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
            onClicked: {
                sendButt(3)
            }
            implicitWidth: 172
            implicitHeight: butth
        }
        Button{
            id : stopRequestButt
            text: "Остановить опрос датчиков"
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
