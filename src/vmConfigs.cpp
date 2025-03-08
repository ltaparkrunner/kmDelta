#include "vmConfigs.h"

//void vmConfigs::dbg_message(QVariant n){
//    qDebug("called ParamsChanged \n");
//}

//void vmConfigs::dbg_message2(QString n){
//    qDebug("called IpChanged \n");
//}


vmConfigs::vmConfigs(configs *cs_, MbtcpClient* tcpC_, tcpIntrfc *parent):
    tcpIntrfc(parent)
    ,cs(cs_)
    ,tcpC(tcpC_)
{
//    connect(this, this->ParamsChanged, this, this->dbg_message);
//    connect(this, this->ipChanged, this, this->dbg_message);
}

void vmConfigs::displayError(QAbstractSocket::SocketError socketError) {

}

void vmConfigs::successConn() {

}

void vmConfigs::connectButt(QString ip_t, QString port_t){
    sendToQml(count);
}

void vmConfigs::periodReqButt(QString ip_t, QString port_t, int t_out){

}

void vmConfigs::setParamsButt(QString ip_t, QString port_t) {
//void vmConfigs::setParamsButt(QVariant n) {
    qDebug("called setParamsButt \n");
}

void vmConfigs::getParamsButt(QString ip_t, QString port_t) {
//QVariant vmConfigs::getParamsButt() {
    QStringList *sl = new QStringList();
    //ip_n = "192.168.10.2";
    sl->append(cs->cnfg.tcpIP);
    sl->append(cs->cnfg.tcpPORT);
    qDebug("called getParamsButt \n");
//    return QVariant(*sl);
}

void vmConfigs::periodReq(/*QString ip_t, QString port_t*/) {

}

void vmConfigs::load_File_Qml()
{
    count++;
    if(cs->load_file_configs("config.ini") < 0) emit sendErrFileOpen("config.ini");
    QList<QString> *str_cs = cs->fillList();

    emit sendCurrIp(*str_cs);
    delete str_cs;
}
void vmConfigs::save_File_Qml(QList<QString> ls)
{
    count++;
    cs->fillCfg(ls);
    if(cs->save_file_configs("config.ini") < 0) emit sendErrFileOpen("config.ini");
    else emit saveFileSucc("config.ini");
    return;
}
void loadDev_readyRead2()
{

}

int vmConfigs::load_Device_Qml()
{
    count++;
    if(!(tcpC->isConnected()))
        if(tcpC->connectTcp(cs->cnfg.tcpIP, cs->cnfg.tcpPORT) < 0) return -1;
    tcpC -> setReadyRead_loadDev(this);
    if(cs->load_tcp_configs(tcpC) < 0) return -2;
    return 0;
}
void vmConfigs::save_Device_Qml()
{
    count++;
    cs->load_file_configs();
    QList<QString> *str_cs = cs->fillList();

    emit sendCurrIp(*str_cs);
    delete str_cs;
}

//void vmConfigs::load_Default_Qml(QString str)
void vmConfigs::load_Default_Qml(QList<QString> str)
//void vmConfigs::load_Default_Qml(QStringList  str)
{
    count++;
    //emit sendToQml2(ip_addr, ip_mask, port);
//    qDebug() << "load_Default_Qml debug:   " << str << "\n";
    qDebug() << "load_Default_Qml debug [0]:   " << str[0] << " [1]: " << str[1] << " [2]: " << str[2]<< " [3]: " << str[3] << "\n";

    cs->load_file_configs();
    QList<QString> *str_cs = cs->fillList();

    emit sendCurrIp(*str_cs);
    delete str_cs;
}
void vmConfigs::commitFromQml(QString ls)
{
    QString temp = cs->cnfg.tcpIP;
    ls.append("for");

    cs->cnfg.tcpIP = ls;
    emit sendCurrIp_2(ls);
 //   cs.load_file_configs();
 //   QList<QString> *str_cs = cs.fillList();

//    emit sendCurrIp(*str_cs);
//    delete str_cs;

    cs->cnfg.tcpIP = temp;
    //messageDialog
}

//void vmConfigs::loadDevice_readyRead(){

//}
//void vmConfigs::saveDevice_readyRead(){

//}

void vmConfigs::loadDev_Respond(){ // This is respond to readyread after return
    count++;
//    cs->load_tcp_configs(tcpC, this);
//    cs->setReadyRead_loadDev(tcpC, this);
}

void vmConfigs::saveDev_Respond(){

}

void vmConfigs::loadChart_Respond(){

}

