import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls

Rectangle {
    id:rect_1
    property var h: [800, 500, 350, 250]
    property int hmax: 1000

    property int ph
    color: "light green"

    RowLayout{
        anchors.fill: parent
        Rectangle{
            color: "teal"          //"blue"
            width: 100
            height: 400
            Layout.alignment: Qt.AlignBottom
            ColumnLayout{
                Rectangle{
                    color: "light blue"
                    width: 50
                    height: 100
                }
                Rectangle{
                    color: "pink"
                    width: 50
                    height: 100
                    Layout.alignment: Qt.AlignBottom
                }
            }
        }
        Rectangle{
            width: 50
            height: 400
            color: "plum"           //"orange"
            Layout.alignment: Qt.AlignBottom
                Rectangle{
                    color: "orange"     //"azure"
                    width: 30
                    height: 150
                    anchors.bottom: rect4.top
                }
                Rectangle{
                    id: rect4
                    color: "aquamarine"
                    width: 30
                    height: 100
                    anchors.bottom: parent.bottom
                }
            }
    }
    Rectangle{
        anchors.fill: parent
        anchors.margins: 30
        color: "red"
    }
}
