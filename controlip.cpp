#include "controlip.h"
//#include "crc32.h"
#include "tcp_req.h"
#include<QDebug>
#include <QObject>

//ControlIp::ControlIp(QObject *parent) : QObject(parent)
ControlIp::ControlIp(tcpMan *parent) : /*QObject(parent),*/ tcpMan(parent)
//ControlIp::ControlIp(QObject *parent) : /*QObject(parent)*/ tcpMan()
    ,count(0)
//    ,tcpC(new MbtcpClient(dynamic_cast<tcpMan*>(this), this))
    ,tcpC(new MbtcpClient(this, this))
    ,ipt("")
    ,portt("")
{
    // tcpC = &tcpC_;
    // count = 0;
    // ipt = "";
    // portt = "";
    QObject::connect(&tm_tcp_req, &QTimer::timeout, this, &ControlIp::periodReq);//QOverload<>::of(&AnalogClock::update));
}

void ControlIp::connectButt(QString ip_t, QString port_t) {
    tcpC->requestNewFortune(ip_t, port_t);
    emit sendToQml(count);
}

void ControlIp::periodReqButt(QString ip_t, QString port_t, int t_out) {
    ipt = ip_t;
    portt = port_t;
    tm_tcp_req.start(3000);
}

void ControlIp::periodReq(/*QString ip_t, QString port_t*/) {
    ret_t rez = tcp_req::period_req();
    if(tcpC->periodReq(ipt,  portt, *(rez.bdata)) > 0) qDebug("success /n");
    else qDebug("fault /n");
}

void ControlIp::setParamsButt(QString ip_t, QString port_t) {
    ret_t rez = tcp_req::set_params();
    if(tcpC->setParams(ip_t,  port_t, *(rez.bdata)) > 0) qDebug("success /n");
    else qDebug("fault /n");
}

//void ControlIp::sendMsgButt() {
void ControlIp::getParamsButt(QString ip_t, QString port_t) {
    ret_t rez = tcp_req::req_param();
//    if(tcpC->request() > 0) qDebug("success /n");
    if(tcpC->getParams(ip_t,  port_t, *(rez.bdata)) > 0) qDebug("success /n");
    else qDebug("fault /n");
}

// void ControlIp::displayError(QAbstractSocket::SocketError socketError){

// }

// void ControlIp::successConn(){}

// void ControlIp::parseMessage(){}

// void ControlIp::getParamsResp(){}

// void ControlIp::setParamsResp(){}

void ControlIp::periodReqResp(){
    qDebug("non-virtual func");
}

