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
//            f1.values = [10, 10, 10, 10, 10, 10]
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
            axisX: BarCategoryAxis {id:ax;  labelsFont : myFont
                categories: ["01", "02", "03", "04", "05", "06", "07", "08" ] }
            BarSet {
                labelFont : myFont
                id:f1; values: [abs[0], abs[1], abs[2], abs[3], abs[4], abs[5], abs[6], abs[7]] }

            axisY: ValueAxis{
                labelsFont : myFont
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
            anchors.leftMargin: 110
            anchors.rightMargin: 50
            anchors.top: parent.top
            anchors.topMargin: 80

            // Text { text: numToString(abs[0]); Layout.alignment: Qt.AlignHCenter; font.pixelSize: 20; /*rotation : 270*/}
            // Text { text: numToString(abs[1]); Layout.alignment: Qt.AlignHCenter; font.pixelSize: 20}
            // Text { text: numToString(abs[2]); Layout.alignment: Qt.AlignHCenter; font.pixelSize: 20}
            // Text { text: numToString(abs[3]); Layout.alignment: Qt.AlignHCenter; font.pixelSize: 20}
            // Text { text: numToString(abs[4]); Layout.alignment: Qt.AlignHCenter; font.pixelSize: 20}
            // Text { text: numToString(abs[5]); Layout.alignment: Qt.AlignHCenter; font.pixelSize: 20}
            // Text { text: numToString(abs[6]); Layout.alignment: Qt.AlignHCenter; font.pixelSize: 20}
            // Text { text: numToString(abs[7]); Layout.alignment: Qt.AlignHCenter; font.pixelSize: 20}
            Rectangle{ Layout.alignment: Qt.AlignHCenter; width:4
            Text { text: numToString(abs[0]); Layout.alignment: Qt.AlignLeft; font.pixelSize: 20; /*rotation : 270*/}}
            Rectangle{ Layout.alignment: Qt.AlignHCenter; width:4
            Text { text: numToString(abs[1]); Layout.alignment: Qt.AlignLeft; font.pixelSize: 20}}
            Rectangle{ Layout.alignment: Qt.AlignHCenter; width:4
            Text { text: numToString(abs[2]); Layout.alignment: Qt.AlignLeft; font.pixelSize: 20}}
            Rectangle{ Layout.alignment: Qt.AlignHCenter; width:4
            Text { text: numToString(abs[3]); Layout.alignment: Qt.AlignLeft; font.pixelSize: 20}}
            Rectangle{ Layout.alignment: Qt.AlignHCenter; width:4
            Text { text: numToString(abs[4]); Layout.alignment: Qt.AlignLeft; font.pixelSize: 20}}
            Rectangle{ Layout.alignment: Qt.AlignHCenter; width:4
            Text { text: numToString(abs[5]); Layout.alignment: Qt.AlignLeft; font.pixelSize: 20}}
            Rectangle{ Layout.alignment: Qt.AlignHCenter; width:4
            Text { text: numToString(abs[6]); Layout.alignment: Qt.AlignLeft; font.pixelSize: 20}}
            Rectangle{ Layout.alignment: Qt.AlignHCenter; width:4
            Text { text: numToString(abs[7]); Layout.alignment: Qt.AlignLeft; font.pixelSize: 20}}
        }
    function numToString(x){
        if(x < 10) return "   " + x.toString()
        if(x < 100) return "  " + x.toString()
        if(x < 1000) return " " + x.toString()
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
