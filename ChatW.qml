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
    color: 'azure'
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
            f1.values = [abs[0], abs[1], abs[2], abs[3], abs[4], abs[5]]
//            f1.values = [10, 10, 10, 10, 10, 10]
        }
    }

    ChartView {
        title: "Stacked Bar series"
        anchors.fill: parent
        legend.alignment: Qt.AlignBottom
        antialiasing: true
        id: chw
        StackedBarSeries {
            id: mySeries
            labelsVisible : false
            axisX: BarCategoryAxis {id:ax
                categories: ["2007", "2008", "2009", "2010", "2011", "2012" ] }
            BarSet {
                id:f1; values: [2, 2, 3, 4, 5, 6] }

        }
    }
//        GridLayout {

        RowLayout{
            id: grid
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.leftMargin: 56
            anchors.rightMargin: 31
            anchors.top: parent.top
            anchors.topMargin: 80
            Text { text: "002"; Layout.alignment: Qt.AlignHCenter; font.pixelSize: 20; rotation : 270}
            Text { text: "002"; Layout.alignment: Qt.AlignHCenter; font.pixelSize: 20}
            Text { text: "003"; Layout.alignment: Qt.AlignHCenter; font.pixelSize: 20}
            Text { text: "004"; Layout.alignment: Qt.AlignHCenter; font.pixelSize: 20}
            Text { text: "005"; Layout.alignment: Qt.AlignHCenter; font.pixelSize: 20}
            Text { text: "006"; Layout.alignment: Qt.AlignHCenter; font.pixelSize: 20}
        }
    function left1(x){
        console.log("mySeries.left  ", x);
        return x+30;
    }
    function right1(x){
        console.log("mySeries.right  ", x);
        return x-15;
    }
}
