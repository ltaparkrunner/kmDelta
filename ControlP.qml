import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
//import QtQuick.Controls.Styles 1.0
import QtQuick.Dialogs 1.1

///import IP_Addr2.qml 1.0

Rectangle{
//Item{
    id:c_ip2
    width: ip_2.width
    color: 'blue'

    Connections {
        target: mvConfigs // Указываем целевое соединение
        /* Объявляем и реализуем функцию, как параметр
         * объекта и с имененем похожим на название сигнала
         * Разница в том, что добавляем в начале on и далее пишем
         * с заглавной буквы
         * */
//        function onSendToQml(count) {
          onSendToQml: {
            bottomText1.text = count // Устанавливаем счётчик в текстовый лейбл
//            messageDialog.show("title")
//            messageDialog.show(qsTr("Button 1 pressed"))
//            onClicked: messageDialog.open()
//            console.log("Point_1")
//            messageDialog.open("title")
//            console.log("Point_1_5")
        }
//        onSendToDialog: {
//            console.log("Point_2")
//            messageDialog.open("title")
//        }
    }
/*
    MessageDialog {
        id: messageDialog
        title: qsTr("May I have your attention, please?")
        text: "Forever"
        standardButtons: MessageDialog.Ok | MessageDialog.Cancel
//        onAccepted: {
            //console.log("And of course ...")
            //Qt.quit()
//        }
//        Component.onCompleted: visible = false
    }
*/
//    MessageDialog {
    MessageDialog{
        id: messageDialog
        title: qsTr("May I have your attention, please?")
        text: qsTr("The document has been modified.")
//        informativeText: "Do you want to save your changes?"
        standardButtons: StandardButton.Ok //| StandardButton.Cancel
//        onAccepted: document.save()
//        modality :Qt.WindowModal
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
//            controlIp.connectButt(ip_2.ip_t, ip_2.port_t)
            messageDialog.open()
        }

    }
    Button{
        id : sendMessButt
        //x: uppText.x;
        //y: connectButt.y + connectButt.height + 10
        //y: connectButt.bottom + 10
        text: "Request params"
        onClicked: {
            mvConfigs.getParamsButt(ip_2.ip_t, ip_2.port_t)
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
                mvConfigs.periodReqButt(ip_2.ip_t, ip_2.port_t, 3000)
            }
        }
//        Button{
//            id : setParamButt
//            text: "Set params"
//            onClicked: {
//                controlIp.setParamsButt(ip_2.ip_t, ip_2.port_t)
//            }
//        }
    }
    }
}
