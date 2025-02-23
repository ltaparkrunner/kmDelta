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
    title : "Chart Window"
    font: myTitleFont
//    background:
//    property int ip_w: Math.max(c_ip.t1.width, t2.width, t3.width) + rect_2 *2
    readonly property int spch: 20
    readonly property font myFontMenu: ({
            family: "Helvetica",
//            pointSize: 20,
            pixelSize: 17,
//            bold: true
        })
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
        font: myFontMenu
        Menu {
            title: qsTr("File")
            font: parent.font
            MenuItem {
                text: qsTr("Connect")
                font: myFontMenu
                onTriggered: Qt.quit();
            }
            MenuItem {
                text: qsTr("Disconnect")
                font: myFontMenu
                onTriggered: Qt.quit();
            }
            MenuItem {
                text: qsTr("Exit")
                font: myFontMenu
                onTriggered: Qt.quit();
            }
        }
        Menu {
            title: qsTr("Properities")
            font: parent.font
            MenuItem {
                text: qsTr("Connect")
                font: myFontMenu
                onTriggered: Qt.quit();
            }
            MenuItem {
                text: qsTr("Disconnect")
                font: myFontMenu
                onTriggered: Qt.quit();
            }
            MenuItem {
                text: qsTr("Exit")
                font: myFontMenu
                onTriggered: Qt.quit();
            }
        }

        Menu {
            title: qsTr("About the program")
            font: parent.font
            MenuItem {
                text: qsTr("Exit")
                font: myFontMenu
                onTriggered: Qt.quit();
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
    Component.onCompleted: {
        vmConfigsChat.rectCompleted_Qml()
//        messageDialog2.open()
    }
}
