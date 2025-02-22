import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls

Rectangle {
    id:rect_1
    // Layout.fillHeight: true
    // Layout.fillWidth: true
//    anchors.fill: parent
//    color: "light yellow"
    property var h: [800, 500, 350, 250]
    property int hmax: 1000

    property int ph
    color: "light green"
    Rectangle{
        anchors.bottom: parent.bottom
        color: "light blue"
        width:300
        height: 400
//        ColumnLayout{
//            Layout.fillHeight: true

            Rectangle{
//                Layout.alignment: Qt.AlignBottom
            color: "blue"
            width: 100
            height: 100
//            Layout.alignment: Qt.AlignBottom
             // Text {
             //     Layout.alignment: Qt.AlignBottom
             //     id: top_txt0
             //     text: qsTr(h[0].toString())
             // }
            }
//         Rectangle{
// //                anchors.horizontalCenter: parent.Center
//             Layout.alignment: Qt.AlignHCenter || Qt.AlignBottom
//             width: 20
//             height: Math.floor((h[0]*ph)/hmax)
//             color: "blue"
//         }
             Rectangle{
//                Layout.alignment: Qt.AlignRight || Qt.AlignTop
                 width: 50
                 height: 100
                color: "orange"
                anchors.bottom: parent.bottom
//             Layout.alignment: Qt.AlignBottom

            }

//         }
    }
}
