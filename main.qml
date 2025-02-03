import QtQuick.Controls.Windows
import QtQuick.Controls.Material

import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtCharts 2.0
//import QtQuick.Controls 1.0
import QtQuick.Controls 2.0     //1.0//2.0
import QtQuick.Dialogs //2.0     //1.2

//import QtQuick.Controls.Basic   // auto
Item {
    id: main1
    width: 640
    height: 480
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
    ColumnLayout{
        spacing: 2
        anchors.fill: parent
        Rectangle {
            Layout.alignment: Qt.AlignCenter
            color: "red"
//            Layout.preferredWidth: 40
            Layout.fillWidth: true
            Layout.fillHeight: true
            RowLayout{
                spacing: 2
                anchors.fill: parent
/*
                Rectangle {
                    Layout.alignment: Qt.AlignRight
                    color: "yellow"
        //            Layout.preferredWidth: 40
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                }
*/
/*
                Rectangle {
                    Layout.alignment: Qt.AlignLeft
                    color: "blue"
        //            Layout.preferredWidth: 40
                    Layout.preferredWidth: parent.width/3
                    Layout.fillHeight: true
                }
*/
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
