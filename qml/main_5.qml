//import QtQuick.Controls.Windows
//import QtQuick.Controls.Material

import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtCharts 2.0
//import QtQuick.Controls 1.0
import QtQuick.Controls 2.15     //1.0//2.0
import QtQuick.Dialogs 1.2
//import QtFont 1.2

//import QtQuick.Controls.Basic   // auto
ApplicationWindow{
    id: main1
    width: 1260
    height: 940
    visible: true
    title : "Обмен с устройствои"

    readonly property int menuh: 35
    readonly property int spch: 10

    Connections {
            target: vmConfigsChat // Указываем целевое соединение

        function onOpenFileSucc(text, title){

            messageDialog2.text = text
            messageDialog2.open()
        }
    }

    menuBar:
       MenuBar{
          contentHeight: 30
        Menu {
            title: {qsTr("Файл")}
            font: parent.font
            height: menuh * 3 + 14
            MenuItem {
                text: qsTr("Соединить")
                onTriggered: ctrlP.sendButt(1);
                height: menuh
            }
            MenuItem {
                text: qsTr("Разъединить")
                onTriggered: ctrlP.sendButt(2);
                height: menuh
            }
            MenuSeparator{}
            MenuItem {
                text: qsTr("Выход")
                onTriggered: Qt.quit();
                height: menuh
            }
        }
        Menu {
            title: qsTr("Настройки")
            font: parent.font
            height: menuh * 6 + 2
            MenuItem {
                text: qsTr("Загрузить из файла")
                onTriggered: ctrlP.sendButt(8);
                height: menuh
            }
            MenuItem {
                text: qsTr("Сохранить настройки в файл")
                onTriggered: ctrlP.sendButt(9);
                height: menuh
            }
            MenuItem {
                text: qsTr("Загрузить из устройства")
                onTriggered: ctrlP.sendButt(7);
                height: menuh
            }
            MenuItem {
                  text: qsTr("Записать в устройство")
                onTriggered: ctrlP.sendButt(6);
                height: menuh
            }
            MenuItem {
                text: qsTr("Загрузить параметры по умолчанию в программу")
                onTriggered: ctrlP.sendButt(12);
                height: menuh
            }
            MenuItem {
                text: qsTr("Установить Дату и Время")
                onTriggered: ctrlP.sendButt(5);
                height: menuh
            }
        }

        Menu {
            title: qsTr("О программе")
            height: menuh + 2
            MenuItem {
                text: qsTr("О программе")
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
            Layout.fillWidth: true
            Layout.fillHeight: true
            RowLayout{
                spacing: 2
                anchors.fill: parent

                ChatW_5{
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                }

                ControlP_5{
                    id: ctrlP
                    Layout.fillHeight: true
                }
            }
        }
        CondLine_5{
            id: bott1
            Layout.fillWidth: true
        }
    }
    MessageDialog{

        id: messageDialog2
        title: qsTr("May I have your attention, please?")
        text: qsTr("The document has been modified.")
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

//    Component.onCompleted: {
//        vmConfigsChat.rectCompleted_Qml()
//    }
}
