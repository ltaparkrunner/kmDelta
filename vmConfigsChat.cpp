#include "vmConfigsChat.h"

//void vmConfigsChat::dbg_message(QVariant n){
//    qDebug("called ParamsChanged \n");
//}

//void vmConfigsChat::dbg_message2(QString n){
//    qDebug("called IpChanged \n");
//}


vmConfigsChat::vmConfigsChat(configs *cs_, MbtcpClient* tcpC_, tcpIntrfc *parent):
    tcpIntrfc(parent)
    ,cs(cs_)
    ,tcpC(tcpC_= new MbtcpClient(this))
{
//    connect(this, this->ParamsChanged, this, this->dbg_message);
//    connect(this, this->ipChanged, this, this->dbg_message);
}

void vmConfigsChat::displayError(QAbstractSocket::SocketError socketError) {
    tcpC -> getErrString();
}

void vmConfigsChat::successConn() {

}

void vmConfigsChat::connectButt(QString ip_t, QString port_t){
    emit sendToQml(count);
}

int vmConfigsChat::periodReqButt(QString ip_t, QString port_t, int t_out){
    //
    if(!(tcpC->checkConnected()))
        if(tcpC->connectTcp(cs->cnfg.tcpIP, cs->cnfg.tcpPORT) < 0) return -1;
    tcpC -> setReadyRead_Chart(this);

    QObject::connect(&probePollTmr, &QTimer::timeout, this, &vmConfigsChat::periodReq);
    probePollTmr.setInterval(300);
    probePollTmr.start();
    periodReq();
    return 0;
}

void vmConfigsChat::setParamsButt(QString ip_t, QString port_t) {
//void vmConfigsChat::setParamsButt(QVariant n) {
    qDebug("called setParamsButt \n");
}

void vmConfigsChat::getParamsButt(QString ip_t, QString port_t) {
//QVariant vmConfigsChat::getParamsButt() {
    QStringList *sl = new QStringList();
    //ip_n = "192.168.10.2";
    sl->append(cs->cnfg.tcpIP);
    sl->append(cs->cnfg.tcpPORT);
    qDebug("called getParamsButt \n");
//    return QVariant(*sl);
}

void vmConfigsChat::periodReq(/*QString ip_t, QString port_t*/) {
    cht->get_tcp_chatdata(tcpC);
}

void vmConfigsChat::load_File_Qml()
{
    count++;
    if(cs->load_file_configs("config.ini") < 0) emit sendErrFileOpen("config.ini");
    QList<QString> *str_cs = cs->fillList();

    emit sendCurrIp(*str_cs);
    delete str_cs;
}
void vmConfigsChat::save_File_Qml(QList<QString> ls)
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

int vmConfigsChat::load_Device_Qml()    // send message to load params from device
{
    count++;
    if(!(tcpC->checkConnected()))
        if(tcpC->connectTcp(cs->cnfg.tcpIP, cs->cnfg.tcpPORT) < 0) return -1;
    tcpC -> setReadyRead_loadDev(this);
    if(cs -> load_tcp_configs(tcpC) < 0) return -2;
    return 0;
}

int vmConfigsChat::save_Device_Qml()    // save params to device
{
    count++;
    if(!(tcpC->checkConnected()))
        if(tcpC->connectTcp(cs->cnfg.tcpIP, cs->cnfg.tcpPORT) < 0) return -1;
    tcpC -> setReadyRead_saveDev(this);
    if(cs -> save_tcp_configs(tcpC) < 0) return -2;
    return 0;
}

void vmConfigsChat::load_Default_Qml(QList<QString> str)
{
    count++;
    qDebug() << "load_Default_Qml debug [0]:   " << str[0] << " [1]: " << str[1] << " [2]: " << str[2]<< " [3]: " << str[3] << "\n";

    cs->cnfg.set_default();
    QList<QString> *str_cs = cs->fillList();

    emit sendCurrIp(*str_cs);
    delete str_cs;
}
void vmConfigsChat::commitFromQml(QString ls)
{
    QString temp = cs->cnfg.tcpIP;
    ls.append("for");

    cs->cnfg.tcpIP = ls;
    emit sendCurrIp_2(ls);
    cs->cnfg.tcpIP = temp;
}

int vmConfigsChat::loadDev_Respond(){ // receive device's respond after send message to load params from device
    if(cs ->load_tcp_configs_resp(tcpC) < 0) return -1;
    QList<QString> *str_cs = cs->fillList();

    emit sendCurrIp(*str_cs);
    delete str_cs;
    return 0;
}

int vmConfigsChat::saveDev_Respond(){  // receive device's respond after send message tosave params to device
    if(cs ->save_tcp_configs_resp(tcpC) < 0) return -1;
    emit sendToMB("Eth", "Successfully saved");
    return 0;
}

int vmConfigsChat::loadChart_Respond(){
    QList<qint32>* li = cht->get_tcp_chatdata_resp(tcpC);
    emit sendToChat(*li);
    delete li;
    return 0;
}

