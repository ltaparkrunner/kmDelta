#include "vmConfigs.h"

void vmConfigs::dbg_message(QVariant n){
    qDebug("called ParamsChanged \n");
}

void vmConfigs::dbg_message2(QString n){
    qDebug("called IpChanged \n");
}

vmConfigs::vmConfigs(configs cs_, tcpMan *parent):
    tcpMan(parent)
    ,cs(cs_)
{
    connect(this, this->ParamsChanged, this, this->dbg_message);
    connect(this, this->ipChanged, this, this->dbg_message);
}

void vmConfigs::displayError(QAbstractSocket::SocketError socketError) {

}
void vmConfigs::successConn() {

}

void vmConfigs::connectButt(QString ip_t, QString port_t){

}
void vmConfigs::periodReqButt(QString ip_t, QString port_t, int t_out){

}
//void vmConfigs::setParamsButt(QString ip_t, QString port_t) {
void vmConfigs::setParamsButt(QVariant n) {
    qDebug("called setParamsButt \n");
}
//void vmConfigs::getParamsButt(QString ip_t, QString port_t) {
QVariant vmConfigs::getParamsButt() {
    QStringList *sl = new QStringList();
//    ip_n = "192.168.10.2";
    sl->append(cs.cnfg.IP);
    sl->append(cs.cnfg.DPORT);
    qDebug("called getParamsButt \n");
    return QVariant(*sl);
}
void vmConfigs::periodReq(/*QString ip_t, QString port_t*/) {

}

QString vmConfigs::ip_n() const {
    qDebug("called getIp \n");
    return(cs.cnfg.IP);
}

void vmConfigs::setIp(QString ip_n){
    qDebug("called setIp \n");
    emit ipChanged(ip_n);
}
