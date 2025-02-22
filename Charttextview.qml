import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls

Rectangle {
    id:rect_1
    Layout.fillHeight: true
    Layout.fillWidth: true
//    color: "light yellow"
    property var h: [800, 500, 350, 250]
    property int hmax: 1000

    property int ph
//    Layout.alignment: Qt.AlignBottom
    color: "light green"
    Rectangle{
        id: rect2
        Layout.fillHeight: true
        Layout.fillWidth: true
//        Layout.alignment: Qt.AlignBottom
        color: "light yellow"
    RowLayout{
        Layout.fillHeight: true
        Layout.fillWidth: true
        spacing: 10
        Layout.alignment: Qt.AlignBottom
        ColumnLayout{

            Layout.alignment: Qt.AlignBottom
             Text {
                 Layout.alignment: Qt.AlignBottom
                 id: top_txt0
                 text: qsTr(h[0].toString())
             }
//         Rectangle{
// //                anchors.horizontalCenter: parent.Center
//             Layout.alignment: Qt.AlignHCenter || Qt.AlignBottom
//             width: 20
//             height: Math.floor((h[0]*ph)/hmax)
//             color: "blue"
//         }
             Text {
//                 anchors.bottom: parent.bottom
                 Layout.alignment: Qt.AlignBottom
                 id: bot_txt0
                 text: qsTr("01")
             }
         }
        ColumnLayout{
            Layout.alignment: Qt.AlignBottom
             Text {
                 id: top_txt1
                 text: qsTr(h[1].toString())
             }
//         Rectangle{
// //                anchors.horizontalCenter: parent.Center
//             Layout.alignment: Qt.AlignHCenter
//             width: 20
//             height: Math.floor((h[1]*ph)/hmax)
//             color: "blue"
//         }
             Text {
//                 anchors.bottom: parent.bottom
                 Layout.alignment: Qt.AlignBottom
                 id: bot_txt1
                 text: qsTr("02")
             }
         }
    }
    function toint(x,y){
        console.log("QML message Math.floor(h[0]/hmax*parent.height)", x);
        console.log("parent.height)", y);
        return x;
    }
    onHeightChanged: {
//        console.log("Rectangle HeightChanged height:", height);
        ph = height
//        chartw.redraw()
    }
    }
}
