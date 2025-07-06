import QtQuick 2.0
import QtCharts 2.1
import QtQuick.Layouts

Rectangle{
    property var abs: [270, 0, 200, 350, 0, 0, 1200, 0];

    property var txt1: Text {text: "0000"; font.pixelSize: 20}
    property int labw: 5 //txt1.implicitWidth
    Connections {
        target: vmConfigsChat
        function onSendToChat(abs){
            let text = Array("нет\nсвязи", "нет\nсвязи", "нет\nсвязи", "нет\nсвязи",
                             "нет\nсвязи", "нет\nсвязи", "нет\nсвязи", "нет\nсвязи");
            for(let i = 0; i < 8; i++){
                if(abs[i] % 2 == 1){
                    text[i] = String((abs[i] - 1)/2) + ".5";
                    abs[i] = (abs[i]-1) / 2;
                }
                else {
                    text[i] = String((abs[i])/2) + "  ";
                    abs[i] = abs[i] / 2;
                }
            }

            f1.values = [abs[0], abs[1], abs[2], abs[3], abs[4], abs[5], abs[6], abs[7]]
            tx0.text = abs[0] === -16384 ? "нет\nсвязи" : text[0]
            tx1.text = abs[1] === -16384 ? "нет\nсвязи" : text[1]
            tx2.text = abs[2] === -16384 ? "нет\nсвязи" : text[2]
            tx3.text = abs[3] === -16384 ? "нет\nсвязи" : text[3]
            tx4.text = abs[4] === -16384 ? "нет\nсвязи" : text[4]
            tx5.text = abs[5] === -16384 ? "нет\nсвязи" : text[5]
            tx6.text = abs[6] === -16384 ? "нет\nсвязи" : text[6]
            tx7.text = abs[7] === -16384 ? "нет\nсвязи" : text[7]
        }
    }

    readonly property font myFont: ({
            family: "Helvetica",
//            pointSize: 20,
            pixelSize: 20,
            bold: false//true
        })
    ChartView {
        title: "Stacked Bar series"
        titleFont: myFont
        anchors.fill: parent
        legend.alignment: Qt.AlignBottom
        antialiasing: true
        id: chw
        StackedBarSeries {

            id: mySeries
            labelsVisible : false
            axisX: BarCategoryAxis {id:ax;
                categories: ["01", "02", "03", "04", "05", "06", "07", "08" ] }
            BarSet {
//                labelFont : myFont
                id:f1; values: [abs[0], abs[1], abs[2], abs[3], abs[4], abs[5], abs[6], abs[7]] }

            axisY: ValueAxis{
//                labelsFont : myFont
                id: axis_Y
                min: 0
                max: 1000
                titleText: "Offset(bias)"
            }
        }
    }

        RowLayout{
            id: grid
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.leftMargin: 95
            anchors.rightMargin: 45
            anchors.top: parent.top
            anchors.topMargin: 80
            Layout.fillWidth: true

            Text { id: tx0; text: /*"----\n----"*/numToString(abs[0]); Layout.alignment: Qt.AlignHCenter; font.pixelSize: 20; width: labw/*rotation : 270*/}
//            Text { id: tx0; text: /*"----\n----"*/numToString(abs[0]); Layout.alignment: Qt.AlignHRight; font.pixelSize: 20; width: labw/*rotation : 270*/}
            Text { id: tx1;  text: numToString(abs[1]); Layout.alignment: Qt.AlignHCenter; font.pixelSize: 20; width: labw}
//            Text { id: tx1;  text: numToString(abs[1]); Layout.alignment: Qt.AlignHRight; font.pixelSize: 20; width: labw}
            Text { id: tx2;  text: numToString(abs[2]); Layout.alignment: Qt.AlignHCenter; font.pixelSize: 20; width: labw}
//            Text { id: tx2;  text: numToString(abs[2]); Layout.alignment: Qt.AlignHRight; font.pixelSize: 20; width: labw}
            Text { id: tx3;  text: numToString(abs[3]); Layout.alignment: Qt.AlignHCenter; font.pixelSize: 20; width: labw}
//            Text { id: tx3;  text: numToString(abs[3]); Layout.alignment: Qt.AlignHRight; font.pixelSize: 20; width: labw}
            Text { id: tx4;  text: numToString(abs[4]); Layout.alignment: Qt.AlignHCenter; font.pixelSize: 20; width: labw}
//            Text { id: tx4;  text: numToString(abs[4]); Layout.alignment: Qt.AlignHRight; font.pixelSize: 20; width: labw}
            Text { id: tx5;  text: numToString(abs[5]); Layout.alignment: Qt.AlignHCenter; font.pixelSize: 20; width: labw}
//            Text { id: tx5;  text: numToString(abs[5]); Layout.alignment: Qt.AlignHRight; font.pixelSize: 20; width: labw}
            Text { id: tx6;  text: numToString(abs[6]); Layout.alignment: Qt.AlignHCenter; font.pixelSize: 20; width: labw}
//            Text { id: tx6;  text: numToString(abs[6]); Layout.alignment: Qt.AlignHRight; font.pixelSize: 20; width: labw}
            Text { id: tx7;  text: numToString(abs[7]); Layout.alignment: Qt.AlignHCenter; font.pixelSize: 20; width: labw}
//            Text { id: tx7;  text: numToString(abs[7]); Layout.alignment: Qt.AlignHRight; font.pixelSize: 20; width: labw}
        }
    function numToString(x){
        if(x < 10) return x.toString() + "   "
        if(x < 100) return x.toString() + "  "
        if(x < 1000) return x.toString() + " "
        else return x.toString()
    }
    function numToString2(x){
        if(x < 10) { console.log("dig length: ", ("___" + x.toString()).length); return "   " + x.toString()}
        if(x < 100) { console.log("dig length: ", ("__" + x.toString()).length); return "  " + x.toString()}
        if(x < 1000) { console.log("dig length: ", ("-" + x.toString()).length); return " " + x.toString()}
        else { console.log("dig length: ", (x.toString()).length); return x.toString()}
    }
    function numToString1(x){
        return (x + 10000).toString().slice(1,5)
    }
}
