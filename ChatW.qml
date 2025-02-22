import QtQuick 2.0
import QtCharts 2.1
import QtQuick.Layouts 1.0
import QtQuick.Controls

Rectangle{
    //id: upp1col1
    //width: main1.width/3 *2
    //height: row1.height
    //Layout.fillHeight: true
    //Layout.fillHeight: true
    //Layout.fillWidth: true
    color: 'azure'

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

    ChartView {
//        title: "Stacked Bar series"
        title:  "490 480 470 460 450 440 430 420"
        anchors.fill: parent
        legend.alignment: Qt.AlignBottom
        antialiasing: true

        ValueAxis{
            id: valueAxisY
            min: 100
            max: 900
            titleText: "Temperature [&deg;C]"
        }

      BarSeries {
            id: mySeries
            axisX: BarCategoryAxis { categories: ["490", "480", "470", "460", "450", "440", "430", "420" ] }
            axisY: valueAxisY
            BarSet { id:f1; values: [490, 490, 490, 490, 490, 490, 490, 490 ] }

            // Rectangle{
            //     anchors.bottom: parent.bottom
            //     anchors.left: parent.left
            //     anchors.right: parent.right
            //     color: "yellow"
            //     height: 40
            //     RowLayout{
            //         ColumnLayout{
            //             Label{text:"MKLP 01" }
            //             Text {
            //                 id: table
            //                 text: qsTr("text")
            //             }
            //         }
            //     }
            // }
        }

//       BarSeries {
//             id: mySeries2
//             axisX: BarCategoryAxis { categories: ["490", "02", "03", "04", "90", "476", "480", "490" ] }
//             axisY: valueAxisY
// //            BarSet { id:f2; values: [490, 490, 490, 490, 490, 490, 490, 490 ] }
//         }
      Rectangle{
          anchors.bottom: parent.bottom
          anchors.left: parent.left
          anchors.right: parent.right
          color: "yellow"
          height: 40
          RowLayout{
              ColumnLayout{
                  Label{text:"MKLP 01" }
                  Text {
                      id: table
                      text: qsTr("text")
                  }
              }
          }
      }
    }
}
