import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtCharts 2.0
import QtQuick.Controls 1.0


Item {
    id: main1
    width: 640
    height: 480
    visible: true
//    property int ip_w: Math.max(c_ip.t1.width, t2.width, t3.width) + rect_2 *2

    Connections {
            target: mvConfigs // Указываем целевое соединение
//            onSendToDialog: {
//                messageDialog.show(title)
//            }
        }

//    signal qmlSignal(msg: string)
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
}
