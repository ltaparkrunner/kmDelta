#include "mvConfigs.h"

mvConfigs::mvConfigs(configs cs_, tcpMan *parent):
    tcpMan(parent)
    ,cs(cs_)
{}

void mvConfigs::displayError(QAbstractSocket::SocketError socketError) {

}
void mvConfigs::successConn() {

}

void mvConfigs::connectButt(QString ip_t, QString port_t){

}
void mvConfigs::periodReqButt(QString ip_t, QString port_t, int t_out){

}
void mvConfigs::setParamsButt(QString ip_t, QString port_t) {

}
void mvConfigs::getParamsButt(QString ip_t, QString port_t) {

}
void mvConfigs::periodReq(/*QString ip_t, QString port_t*/) {

}
