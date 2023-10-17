import QtQuick 2.0

Rectangle{
    //Layout.maximumHeight: 480//parent.height
    //Layout.maximumWidth: 640//parent.width
    //width: main1.width
    //height: main1.height/2
    //x:
    //y: upp1.bottom
    //bottom: main1.bottom
    color: 'green'
    Text{
        id: bottomText3
        x: 10;
        y: 10
        text: '00:00:00'
    }
    Text{
        id: bottomText4
        x: bottomText3.x;
        y: bottomText3.y + bottomText3.height + 10
        text: '00'
    }
}
