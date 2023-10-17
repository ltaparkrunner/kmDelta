#include "controlip.h"

ControlIp::ControlIp(QObject *parent) : QObject(parent)
{
    count = 0;
}

void ControlIp:: receiveFromQml()
{
    count++;
    emit sendToQml(count);
}

