#include "controlip.h"
#include<QDebug>

//ControlIp::ControlIp(QObject *parent) : QObject(parent)
ControlIp::ControlIp(MbtcpClient &tcpC_, QObject *parent) : QObject(parent)
{
    tcpC = &tcpC_;
    count = 0;
}

void ControlIp::connectButt(QString ip_t, QString port_t) {
    tcpC->requestNewFortune(ip_t, port_t);
    emit sendToQml(count);
}

void ControlIp::periodReqButt(QString ip_t, QString port_t) {
    if(tcpC->periodReq() > 0) qDebug("success /n");
    else qDebug("fault /n");
}

void ControlIp::setParamButt(QString ip_t, QString port_t) {
    if(tcpC->setParam() > 0) qDebug("success /n");
    else qDebug("fault /n");
}

void ControlIp::sendMsgButt() {
    if(tcpC->request() > 0) qDebug("success /n");
    else qDebug("fault /n");
}
