//import QtQuick.Controls.Windows
//import QtQuick.Controls.Material

import QtQuick 2.4
import QtQuick.Layouts 1.0
import QtCharts 2.0
//import QtQuick.Controls 1.0
import QtQuick.Controls 1.4     //1.0//2.0
import QtQuick.Dialogs 1.2//2.0     //1.2
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

ApplicationWindow{
    id: main1
    width: 960
    height: 640
    visible: true
//    background:
//    property int ip_w: Math.max(c_ip.t1.width, t2.width, t3.width) + rect_2 *2

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
        Menu {
            title: qsTr("File")

            MenuItem {
                text: qsTr("Connect")
                onTriggered: Qt.quit();
            }
            MenuItem {
                text: qsTr("Disconnect")
                onTriggered: Qt.quit();
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
        Menu {
            title: qsTr("Properities")

            MenuItem {
                text: qsTr("Connect")
                onTriggered: Qt.quit();
            }
            MenuItem {
                text: qsTr("Disconnect")
                onTriggered: Qt.quit();
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }

        Menu {
            title: qsTr("About the program")

            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    ColumnLayout{
        spacing: 2
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
    Component.onCompleted: {
        vmConfigsChat.rectCompleted_Qml()
//        menu.open()
//        messageDialog2.open()
    }
}
