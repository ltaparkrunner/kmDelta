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
            color: "blue"
            width: 100
            height: 100
            Layout.alignment: Qt.AlignBottom
        }
        Rectangle{
            width: 50
            height: 100
            color: "orange"
            Layout.alignment: Qt.AlignBottom
        }
    }
}
