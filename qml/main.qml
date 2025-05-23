//import QtQuick.Controls.Windows
//import QtQuick.Controls.Material

import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtCharts 2.0
//import QtQuick.Controls 1.0
import QtQuick.Controls //2.0     //1.0//2.0
import QtQuick.Dialogs //2.0     //1.2

//import QtQuick.Controls.Basic   // auto
ApplicationWindow{
//Item {
    readonly property font myTitleFont: ({
            family: "Helvetica",
//            pointSize: 20,
            pixelSize: 25,
            bold: false//true
        })
    id: main1
    width: 1260
    height: 940
    visible: true
    title : "Обмен с устройствои"

    readonly property int menuh: 35
    readonly property int spch: 10
//    readonly property font myFontMenu: ({
//            family: "Helvetica",
////            pointSize: 20,
//            pixelSize: 17,
////            bold: true
//        })
    Connections {
            target: vmConfigsChat // Указываем целевое соединение
//            onSendToDialog: {
//                messageDialog.show(title)
//            }
        function onOpenFileSucc(text, title){
//        onOpenFileSucc:{
//            messageDialog2.setText(text)
//            messageDialog2.text = text
            messageDialog2.text = text
            messageDialog2.open()
        }
    }

    menuBar:
       MenuBar{
//        font: myFontMenu
          contentHeight: 30
//          height: 30
        Menu {
            title: {qsTr("Файл")}
            font: parent.font
            height: menuh * 3 + 14
            MenuItem {
                //text: qsTr("Connect")
                text: qsTr("Соединить")
//                font: myFontMenu
                onTriggered: Qt.quit();
                height: menuh
            }
            MenuItem {
//                text: qsTr("Disconnect")
                text: qsTr("Разъединить")
//                font: myFontMenu
                onTriggered: Qt.quit();
                height: menuh
            }
            MenuSeparator{}
            MenuItem {
//                text: qsTr("Exit")
                text: qsTr("Выход")
//                font: myFontMenu
                onTriggered: Qt.quit();
                height: menuh
            }
        }
        Menu {
//            title: qsTr("Properities")
            title: qsTr("Настройки")
            font: parent.font
            height: menuh * 6 + 2
            MenuItem {
//                text: qsTr("Load_From_File")
                text: qsTr("Загрузить из файла")
//                font: myFontMenu
                onTriggered: Qt.quit();
                height: menuh
            }
            MenuItem {
//                text: qsTr("Save_To_File")
                text: qsTr("Сохранить настройки в файл")
//                font: myFontMenu
                onTriggered: Qt.quit();
                height: menuh
            }
            MenuItem {
//                text: qsTr("Load_From_Device")
                text: qsTr("Загрузить из устройства")
//                font: myFontMenu
                onTriggered: Qt.quit();
                height: menuh
            }
            MenuItem {
//                text: qsTr("Save_To_Device")
                  text: qsTr("Записать в устройство")
//                font: myFontMenu
                onTriggered: Qt.quit();
                height: menuh
            }
            MenuItem {
//                text: qsTr("Load_Defaults")
                text: qsTr("Загрузить параметры по умолчанию в программу")
//                font: myFontMenu
                onTriggered: Qt.quit();
                height: menuh
            }
            MenuItem {
//               text: qsTr("Set_Date_Time")
                text: qsTr("Установить Дату и Время")
//                font: myFontMenu
                onTriggered: Qt.quit();
                height: menuh
            }
        }

        Menu {
 //           title: qsTr("About " + main1.title)
            title: qsTr("О программе")
            height: menuh + 2
            MenuItem {
                text: qsTr("О программе")
//                font: myFontMenu
                onTriggered: aboutDialog.open();
                height: menuh
            }
        }
    }

    ColumnLayout{
        spacing: spch
        anchors.fill: parent
        Rectangle {
            Layout.alignment: Qt.AlignCenter
            color: "white"
//            Layout.preferredWidth: 40
            Layout.fillWidth: true
            Layout.fillHeight: true
            RowLayout{
                spacing: 2
                anchors.fill: parent

                ChatW{
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                }

                ControlP{
                    //id: c_ip
                    //Layout.preferredWidth:  parent.width/3
                    //Layout.preferredWidth:   child.width//c_ip2.width    //270//ip_contain.width

                    //Layout.fillWidth: true
                    Layout.fillHeight: true
                }
            }
        }
/*
        Rectangle {
            Layout.alignment: Qt.AlignLeft
            color: "green"
//            Layout.preferredWidth: 40
            Layout.fillWidth: true
            Layout.preferredHeight: parent.height/3
        }
*/
        CondLine{
            id: bott1
//            height: parent.height/3
            Layout.fillWidth: true
//            Layout.preferredHeight: parent.height/3
            //Layout.fillHeight: true
        }
    }
    MessageDialog{

        id: messageDialog2
        title: qsTr("May I have your attention, please?")
        text: qsTr("The document has been modified.")
//        width: 300
    }
    MessageDialog{
        id: aboutDialog
        title: qsTr("О программе \"Chart Window\"")
        text: qsTr( "\"Chart Window\" \n \
        (c) ОАО \"Авангард\"\n \
   Санкт-Петербург, Кондратьевский пр., д.72,\n\
                   \n\
      Разработчики: \n\
        Игнатьев В.С. \n\
        Мордвинцев А.Л.")
    }

    Component.onCompleted: {
        vmConfigsChat.rectCompleted_Qml()
//        messageDialog2.open()
    }
}
