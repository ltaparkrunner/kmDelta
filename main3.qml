import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Window 2.15

ApplicationWindow{
    title: qsTr("Hello World")
    width: 640
    height: 480
        visible: true
    menuBar:
       MenuBar{
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    Button{
        text: qsTr("Hello World")
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }
}
