import QtQuick 2.0
import QtCharts 2.1
import QtQuick.Layouts

Rectangle{

    //id: upp1col1
    //width: main1.width/3 *2
    //height: row1.height
    //Layout.fillHeight: true
    //Layout.fillHeight: true
    //Layout.fillWidth: true
    property var abs: [270, 0, 200, 350, 0, 0, 1200, 0];

    property var txt1: Text {text: "0000"; font.pixelSize: 20}
    property int labw: txt1.implicitWidth
//color:    color: 'azure'
//    anchors.fill: parent
    Connections {
        target: vmConfigsChat // Указываем целевое соединение
        /* Объявляем и реализуем функцию, как параметр
         * объекта и с имененем похожим на название сигнала
         * Разница в том, что добавляем в начале on и далее пишем
         * с заглавной буквы
         * */
        function onSendToChat(abs){
//        onSendToChat: {
//            bottomText1.text = count // Устанавливаем счётчик в текстовый лейбл
//            f1.values = [abs[0],10,10,10,10,10]
            f1.values = [abs[0], abs[1], abs[2], abs[3], abs[4], abs[5], abs[6], abs[7]]
            tx0.text = abs[0] = -16384 ? "нет\nсвязи" : abs[0]
            tx1.text = abs[1] = -16384 ? "нет\nсвязи" : abs[1]
            tx2.text = abs[2] = -16384 ? "нет\nсвязи" : abs[2]
            tx3.text = abs[3] = -16384 ? "нет\nсвязи" : abs[3]
            tx4.text = abs[4] = -16384 ? "нет\nсвязи" : abs[4]
            tx5.text = abs[5] = -16384 ? "нет\nсвязи" : abs[5]
            tx6.text = abs[6] = -16384 ? "нет\nсвязи" : abs[6]
            tx7.text = abs[7] = -16384 ? "нет\nсвязи" : abs[7]
        }
    }

//    readonly property font myFont: ({
//            family: "Helvetica",
////            pointSize: 20,
//            pixelSize: 20,
//            bold: false//true
//        })
    ChartView {
        title: "Stacked Bar series"
//        titleFont: myFont
        anchors.fill: parent
        legend.alignment: Qt.AlignBottom
        antialiasing: true
        id: chw
        StackedBarSeries {

            id: mySeries
            labelsVisible : false
            axisX: BarCategoryAxis {id:ax;  //labelsFont : myFont
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
//        GridLayout {
        // Rectangle{
        //     anchors.right: parent.right
        //     anchors.left: parent.left
        //     anchors.leftMargin: 95
        //     anchors.rightMargin: 35
        //     anchors.top: parent.top
        //     anchors.topMargin: 80
        //     height: 20
        //     color: "yellow"
        // }

        RowLayout{
            id: grid
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.leftMargin: 95
            anchors.rightMargin: 35
            anchors.top: parent.top
            anchors.topMargin: 80
            Layout.fillWidth: true

            Text { id: tx0; text: /*"----\n----"*/numToString(abs[0]); Layout.alignment: Qt.AlignHCenter; font.pixelSize: 20; width: labw/*rotation : 270*/}
            Text { id: tx1;  text: numToString(abs[1]); Layout.alignment: Qt.AlignHCenter; font.pixelSize: 20; width: labw}
            Text { id: tx2;  text: numToString(abs[2]); Layout.alignment: Qt.AlignHCenter; font.pixelSize: 20; width: labw}
            Text { id: tx3;  text: numToString(abs[3]); Layout.alignment: Qt.AlignHCenter; font.pixelSize: 20; width: labw}
            Text { id: tx4;  text: numToString(abs[4]); Layout.alignment: Qt.AlignHCenter; font.pixelSize: 20; width: labw}
            Text { id: tx5;  text: numToString(abs[5]); Layout.alignment: Qt.AlignHCenter; font.pixelSize: 20; width: labw}
            Text { id: tx6;  text: numToString(abs[6]); Layout.alignment: Qt.AlignHCenter; font.pixelSize: 20; width: labw}
            Text { id: tx7;  text: numToString(abs[7]); Layout.alignment: Qt.AlignHCenter; font.pixelSize: 20; width: labw}
//            Rectangle{ Layout.alignment: Qt.AlignHCenter; implicitWidth: labw;// height: 1;/*implicitHeight: tx0.implicitHeight;*/ color:"light green";//opacity: 0;/*Layout.fillWidth: true;*/ /*Layout.fillHeight: true;*///height: 5;//implicitWidth: tx0//width:4;//  color:"green"
//            Text { id: tx0; text: numToString(abs[0]); anchors.horizontalCenter: parent.horizontalCenter; font.pixelSize: 20; /*rotation : 270*/}}
//            Rectangle{ Layout.alignment: Qt.AlignHCenter; implicitWidth: labw; //height: 1;/*implicitHeight: tx1.implicitHeight;*/ /*Layout.fillWidth: true;*/ color:"light green"; /*Layout.fillHeight: true;*///height: 5;//implicitWidth: tx1// width:4; //height: 5; color:"blue"
//            Text { id: tx1; text: numToString(abs[1]); anchors.horizontalCenter: parent.horizontalCenter; font.pixelSize: 20}}
//            Rectangle{ Layout.alignment: Qt.AlignHCenter;  implicitWidth: labw; //height: 1;/*implicitHeight: tx2.implicitHeight;*/ color:"light green";//height: 5;//implicitWidth: tx2//width:4
//            Text { id: tx2; text: numToString(abs[2]); anchors.horizontalCenter: parent.horizontalCenter; font.pixelSize: 20}}
//            Rectangle{ Layout.alignment: Qt.AlignHCenter;  implicitWidth: labw; //height: 1;/*implicitHeight: tx3.implicitHeight;*/ color:"light green";//height: 5;//implicitWidth: tx3//width:4
//            Text { id: tx3; text: numToString(abs[3]); anchors.horizontalCenter: parent.horizontalCenter; font.pixelSize: 20}}
//            Rectangle{ Layout.alignment: Qt.AlignHCenter;  implicitWidth: labw; //height: 1;/*implicitHeight: tx4.implicitHeight;*/ color:"light green";//height: 5;//implicitWidth: tx4//width:4
//            Text { id: tx4; text: numToString(abs[4]); anchors.horizontalCenter: parent.horizontalCenter; font.pixelSize: 20}}
//            Rectangle{ Layout.alignment: Qt.AlignHCenter;  implicitWidth: labw; //height: 1;/*implicitHeight: tx5.implicitHeight;*/ color:"light green";//height: 5;//implicitWidth: tx5// width:4
//            Text { id: tx5; text: numToString(abs[5]); anchors.horizontalCenter: parent.horizontalCenter; font.pixelSize: 20}}
//            Rectangle{ Layout.alignment: Qt.AlignHCenter;  implicitWidth: labw; //height: 1;/*implicitHeight: tx6.implicitHeight;*/ color:"light green";//opacity: 0;//height: 5;//implicitWidth: tx6// width:4
//            Text { id: tx6; text: numToString(abs[6]); anchors.horizontalCenter: parent.horizontalCenter; font.pixelSize: 20; opacity: 100;}}
//            Rectangle{ Layout.alignment: Qt.AlignHCenter;  implicitWidth: labw; //height: 1;/*implicitHeight: tx7.implicitHeight;*/ color:"light green";//height: 5;//implicitWidth: tx7// width:4
//            Text { id: tx7; text: numToString(abs[7]); anchors.horizontalCenter: parent.horizontalCenter; font.pixelSize: 20}}
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
    // function left1(x){
    //     console.log("mySeries.left  ", x);
    //     return x+30;
    // }
    // function right1(x){
    //     console.log("mySeries.right  ", x);
    //     return x-15;
    // }
}
