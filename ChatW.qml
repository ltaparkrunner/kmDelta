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
    ChartView {
        title: "Stacked Bar series"
        anchors.fill: parent
        legend.alignment: Qt.AlignBottom
        antialiasing: true

        StackedBarSeries {
            id: mySeries
            axisX: BarCategoryAxis { categories: ["2007", "2008", "2009", "2010", "2011", "2012" ] }
            BarSet { label: "Bob"; values: [2, 2, 3, 4, 5, 6] }
            BarSet { label: "Susan"; values: [5, 1, 2, 4, 1, 7] }
            BarSet { label: "James"; values: [3, 5, 8, 13, 5, 8] }
        }
    }
}
