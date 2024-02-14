import QtQuick 2.0
import QtCharts 2.1

Rectangle{
    //id: upp1col1
    //width: main1.width/3 *2
    //height: row1.height
    //Layout.fillHeight: true
    //Layout.fillHeight: true
    //Layout.fillWidth: true
    color: 'azure'

    Connections {
        target: vmConfigs // Указываем целевое соединение
        /* Объявляем и реализуем функцию, как параметр
         * объекта и с имененем похожим на название сигнала
         * Разница в том, что добавляем в начале on и далее пишем
         * с заглавной буквы
         * */
//        function onSendToQml(count) {
        onSendToChat: {
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

        StackedBarSeries {
            id: mySeries
            axisX: BarCategoryAxis { categories: ["2007", "2008", "2009", "2010", "2011", "2012" ] }
            BarSet { id:f1; values: [2, 2, 3, 4, 5, 6] }
    //        BarSet { id:f1; label: "Bob"; values: [2, 2, 3, 4, 5, 6] }
    //        BarSet { label: "Susan"; values: [5, 1, 2, 4, 1, 7] }
    //        BarSet { label: "James"; values: [3, 5, 8, 13, 5, 8] }
        }
    }
}
