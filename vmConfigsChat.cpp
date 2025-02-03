#include "vmConfigsChat.h"
#include <QtTest/QTest>
#include <QMessageBox>
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
    ,pointTmr(new pointTimer())
{
//    connect(this, this->ParamsChanged, this, this->dbg_message);
//    connect(this, this->ipChanged, this, this->dbg_message);
    connect(pointTmr->getTmrPtr(), &QTimer::timeout, this, &tcpIntrfc::timeout_Respond );
    connect(pointTmr, &pointTimer::expired, this, &vmConfigsChat::expired_Respond);
    // connect(tcpSocket, &QAbstractSocket::errorOccurred,
    //         tcpm, &tcpIntrfc::displayError);
}

//void vmConfigsChat::displayError(QAbstractSocket::SocketError socketError) {
void vmConfigsChat::displayError() {
    pointTmr->stopTmr();
    QString st = tcpC -> getErrString();
    emit sendToMB("Eth_1", st);
}

void vmConfigsChat::successConn() {
    pointTmr->stopTmr();

    if(tcpC->checkConnected()) emit sendToMB("Eth_2", "Successfully connected to device over Ethernet");
    else emit sendToMB("Eth_3", "Something strange");
}

void vmConfigsChat::connectButt(QString ip_t, QString port_t){
//    QString ip = cs->cnfg.tcpIP, port = cs->cnfg.tcpPORT;
    tcpC -> connectTcp(cs->cnfg.tcpIP, cs->cnfg.tcpPORT);
//    tcpC -> connectTcp(ip, port);
//    tcpC -> connectTcp(ip_t, port_t);
    pointTmr->setTmr(1500,"Attempt to connect");
    emit sendToMB("TCP", "Attempt to connect");
//    pointTmr->tmr.setInterval(1500);
//    connect(&pointTmr->tmr, &QTimer::timeout, this, &vmConfigsChat::tmrAddPoint);
//    pointTmr->tmr.start();
//    emit sendToQml(count);
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

int vmConfigsChat::rectCompleted_Qml(){
    if(cs->load_file_configs("config.ini") < 0) emit sendErrFileOpen("config.ini");
//    else emit openFileSucc("Can't open config.ini", "failure");
    QList<QString> *str_cs = cs->fillList();

    emit sendCurrIp(*str_cs);
    delete str_cs;
//    QTest::qWait(5000);
//    emit openFileSucc("Can't open config.ini", "failure");
    QMessageBox msgBox;
    msgBox.setText("The document has been modified.");
    msgBox.setInformativeText("Do you want to save your changes?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    int ret = msgBox.exec();

    QTimer::singleShot(50, this, &vmConfigsChat::sendMess);
    return ret;
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
    if(cs ->load_tcp_configs_resp(tcpC) < 0)
        return -1;
    QList<QString> *str_cs = cs->fillList();

    emit sendCurrIp(*str_cs);
    delete str_cs;
    return 0;
}

int vmConfigsChat::saveDev_Respond(){  // receive device's respond after send message tosave params to device
    if(cs ->save_tcp_configs_resp(tcpC) < 0) return -1;
    emit sendToMB("Eth_4", "Successfully saved");
    return 0;
}

int vmConfigsChat::loadChart_Respond(){
    QList<qint32>* li = cht->get_tcp_chatdata_resp(tcpC);
    emit sendToChat(*li);
    delete li;
    return 0;
}

int vmConfigsChat::timeout_Respond() {
    QString str = pointTmr->incriment();
    emit sendToMB("Eth_5", str);
    return 0;
}

void vmConfigsChat::sendMess(){
    emit openFileSucc("Can't open config.ini", "failure");
}

void vmConfigsChat::expired_Respond(){
    tcpC->disconnectTcp();
    pointTmr->stopTmr();
    emit sendToMB("Eth_6", "Error:  Connection timed out.");
}
