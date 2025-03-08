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
    ,cht(new chat())
    ,msg_type(nomsg)
    ,conn_dir(idle)
    ,conn_c(disconn)
    ,butt(noneB)
//    ,w_buf(QByteArray(ba_len, 0))
{
//    connect(this, this->ParamsChanged, this, this->dbg_message);
//    connect(this, this->ipChanged, this, this->dbg_message);
    connect(pointTmr->getTmrPtr(), &QTimer::timeout, this, &tcpIntrfc::timeout_Respond );
    connect(pointTmr, &pointTimer::expired, this, &vmConfigsChat::expired_Respond);
//    connect(tcpC->getTcpSocket(), &QIODevice::readyRead, this, &vmConfigsChat::tcpDevRespond);
    connect(tcpC->getTcpSocket(), &QTcpSocket::readyRead, this, &vmConfigsChat::tcpDevRespond);
    connect(tcpC->getTcpSocket(), &QAbstractSocket::connected, this, &vmConfigsChat::successConn);
    connect(tcpC->getTcpSocket(), &QAbstractSocket::disconnected, this, &vmConfigsChat::successDisconn);
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
    conn_dir = idle;
    if(tcpC->isConnected()) emit sendToMB("Eth_2", "Successfully connected to device over Ethernet");
    else emit sendToMB("Eth_3", "Something strange");
    if((int)butt > 0 && (int)butt < buttAmount) butt_proc();
}

void vmConfigsChat::successDisconn() {
    pointTmr->stopTmr();
    conn_dir = idle;
    if(!tcpC->isConnected()) emit sendToMB("Eth_14", "Successfully disconnected to device");
    else emit sendToMB("Eth_15", "Something strange");
//    if((int)butt > 0 && (int)butt < buttAmount) {
//        emit sendToMB("TCP", "Attempt to connect");
//        tcpC->connectTcp(cs->cnfg.tcpIP, cs->cnfg.tcpPORT);
//    }
    switch(butt){
        case connectB:
        case periodReqB:
        case setTimeB:
        case setParamsB:
        case getParamsB:
        case loadDeviceB:
        case saveDeviceB:
            emit sendToMB("TCP", "Attempt to connect");
            tcpC->connectTcp(cs->cnfg.tcpIP, cs->cnfg.tcpPORT);
            break;
        case disconnectB:
            butt_proc();
            break;
        default: break;
    }
//    else emit sendToMB("TCP", "Already connected");
//    pointTmr->tmr.setInterval(1500);
//    connect(&pointTmr->tmr, &QTimer::timeout, this, &vmConfigsChat::tmrAddPoint);
//    pointTmr->tmr.start();
//    emit sendToQml(count);
//    return 0;
}

// int vmConfigsChat::disconnectButt(QString ip_t, QString port_t){
// //    QString ip = cs->cnfg.tcpIP, port = cs->cnfg.tcpPORT;
//     tcpC -> disconnectTcp();
//     conn_dir = disconnecting;
//     pointTmr->setTmr(1500,"Attempt to disconnect", disconnecting);
//     emit sendToMB("TCP", "Attempt to disconnect");
//     return 0;
// }
// int vmConfigsChat::periodReqButt(QString ip_t, QString port_t, int t_out){
//     //
//     if(!(tcpC->isConnected()))
//         if(tcpC->connectTcp(cs->cnfg.tcpIP, cs->cnfg.tcpPORT) < 0) return -1;
//     tcpC -> setReadyRead_Chart(this);

// //    QObject::connect(&probePollTmr, &QTimer::timeout, this, &vmConfigsChat::periodReq);
//     QObject::connect(&probePollTmr, &QTimer::timeout, this, &vmConfigsChat::getSensorsTransmit);
//     probePollTmr.setInterval(300);
//     probePollTmr.start();
// //    periodReq();
//     getSensorsTransmit();
//     return 0;
// }

int vmConfigsChat::stopReqButt(QString ip_t, QString port_t, int t_out){
    if(tcpC->isConnected())     tcpC -> disconnectTcp();
    probePollTmr.stop();
    return 0;
}

// int vmConfigsChat::setTimeButt(QString ip_t, QString port_t, int t_out){
//     setRTCTransmit();
//     return 0;
// }
// void vmConfigsChat::setParamsButt(QString ip_t, QString port_t) {
//     setParamsTransmit();
//     qDebug("called setParamsButt \n");
// }

// void vmConfigsChat::getParamsButt(QString ip_t, QString port_t) {
//     getParamsTransmit();
// }

void vmConfigsChat::periodReq(/*QString ip_t, QString port_t*/) {
    cht->get_tcp_chatdata(tcpC);
}

// void vmConfigsChat::load_File_Qml()
// {
//     count++;
//     if(cs->load_file_configs("config.ini") < 0) emit sendErrFileOpen("config.ini");
//     QList<QString> *str_cs = cs->fillList();

//     emit sendCurrIp(*str_cs);
//     delete str_cs;
// }

int vmConfigsChat::rectCompleted_Qml(){
    if(cs->load_file_configs("config.ini") < 0) emit sendErrFileOpen("config.ini");
//    else emit openFileSucc("Can't open config.ini", "failure");
    QList<QString> *str_cs = cs->fillList();

    emit sendCurrIp(*str_cs);
    delete str_cs;
//    QTest::qWait(5000);
//    emit openFileSucc("Can't open config.ini", "failure");
//    QMessageBox msgBox;
//    msgBox.setText("The document has been modified.");
//    msgBox.setInformativeText("Do you want to save your changes?");
//    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
//    msgBox.setDefaultButton(QMessageBox::Save);
//    int ret = msgBox.exec();

//    QTimer::singleShot(50, this, &vmConfigsChat::sendMesg);
    return 0;       //ret;
}

// void vmConfigsChat::save_File_Qml(QList<QString> ls)
// {
//     count++;
//     cs->fillCfg(ls);
//     if(cs->save_file_configs("config.ini") < 0) emit sendErrFileOpen("config.ini");
//     else emit saveFileSucc("config.ini");
//     return;
// }
// void loadDev_readyRead2()
// {

// }

int vmConfigsChat::loadDeviceButt()    // send message to load params from device
{
    count++;
    if(!(tcpC->isConnected()))
        if(tcpC->connectTcp(cs->cnfg.tcpIP, cs->cnfg.tcpPORT) < 0) return -1;
    tcpC -> setReadyRead_loadDev(this);
    if(cs -> load_tcp_configs(tcpC) < 0) return -2;
    return 0;
}

int vmConfigsChat::saveDeviceButt()    // save params to device
{
    count++;
    if(!(tcpC->isConnected()))
        if(tcpC->connectTcp(cs->cnfg.tcpIP, cs->cnfg.tcpPORT) < 0) return -1;
    tcpC -> setReadyRead_saveDev(this);
//    if(cs -> save_tcp_configs(tcpC) < 0) return -2;
    return 0;
}

// void vmConfigsChat::load_Default_Qml(QList<QString> str)
// {
//     count++;
//     qDebug() << "load_Default_Qml debug [0]:   " << str[0] << " [1]: " << str[1] << " [2]: " << str[2]<< " [3]: " << str[3] << "\n";

//     cs->cnfg.set_default();
//     QList<QString> *str_cs = cs->fillList();

//     emit sendCurrIp(*str_cs);
//     delete str_cs;
// }
// void vmConfigsChat::commitFromQml(QString ls)
// {
//     QString temp = cs->cnfg.tcpIP;
//     ls.append("for");

//     cs->cnfg.tcpIP = ls;
//     emit sendCurrIp_2(ls);
//     cs->cnfg.tcpIP = temp;
// }

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
    // QList<qint32>* li = cht->get_tcp_chatdata_resp(tcpC);
    // emit sendToChat(*li);
    // delete li;
    return 0;
}

int vmConfigsChat::timeout_Respond() {
    if(conn_dir == connecting && tcpC->isConnected()){
        emit sendToMB("Eth_17", "Successfully connected to device");
        pointTmr->stopTmr();
        conn_dir = idle;
        return 0;
    }
    else     if(conn_dir == disconnecting && (!tcpC->isConnected())){
        emit sendToMB("Eth_18", "Successfully disconnected to device");
        pointTmr->stopTmr();
        conn_dir = idle;
        return 0;
    }
    else if(conn_dir == idle){
        emit sendToMB("Eth_19", "Something strange with timer");
        pointTmr->stopTmr();
        return 0;
    }

    QString str = pointTmr->incriment();
    emit sendToMB("Eth_5", str);
    return 0;
}

void vmConfigsChat::sendMesg(){
    emit openFileSucc("Can't open config.ini", "failure");
}

void vmConfigsChat::expired_Respond(){
    tcpC->disconnectTcp();
    pointTmr->stopTmr();
    emit sendToMB("Eth_6", "Error:  Connection timed out.");
}

send_t  vmConfigsChat::getParamsTransmit() {
    const int getParams_buf_len = 11;
    QByteArray w_buf(getParams_buf_len,0);
    w_buf[0] = 'G';//Convert.ToByte('G');//Идификатор транзакции
    w_buf[1] = 'B';//Идификатор транзакции
    w_buf[2] = 0x00;//Идификатор протокола
    w_buf[3] = 0x00;//Идификатор протокола
    w_buf[4] = 0;//Длина
    w_buf[5] = 6;//Длина
    w_buf[6] = 'A';//Адрес
    w_buf[7] = 0x03;//Функциональный код
    w_buf[8] = 0;//Адрес первого регистра
    w_buf[9] = 0x33;//Адрес первого регистра
    w_buf[10] = 0;

    if(!tcpC->isConnected()) {
        tcpC->connectTcp(cs->cnfg.tcpIP, cs->cnfg.tcpPORT);
        delay(2000);
        if(!tcpC->isConnected()) {
            msg_type = getParamsErr;
            return getParamsErr;
        }
    }
    if(tcpC->sendToTcp(&w_buf) == w_buf.length()) {
        msg_type = getParams;
        return getParams;
    }
    msg_type = getParamsErr;
    return getParamsErr;
}

int vmConfigsChat::tcpDevRespond(/*QByteArray r_buf*/){
    QByteArray r_buf = tcpC->getAll();
//    qDebug() << "r_buf.length: " << r_buf.length() << " msg_type: " << msg_type << "/n";
    switch(msg_type){
    case getParams:
//        qDebug() << "getParams " << " r_buf.length: " << r_buf.length() << "/n";
        if(cs->parse_tcp_resp(r_buf) == 0) {
//            cs->save_file_configs();
            QList<QString> *str_cs = cs->fillList();
            emit sendCurrIp(*str_cs);
        }
        break;
    case getSensors:
        qDebug() << "getSensors " << "r_buf.length: " << r_buf.length() << "/n";
    {
        static int counter;

        if(counter > 0x0fffffff) counter = 0;
//        qDebug() << "getSensors " << counter << "r_buf.length: " << r_buf.length() << "/n";
        counter++;
        QList<qint32> sens = cht->parse_tcp_resp(r_buf);
        emit sendToChat(sens);
        emit sendTimeDate(cht->getDate(), cht->getTime());
    }
        break;
    case setParams:
    {
        qDebug() << "setParams " << " r_buf.length: " << r_buf.length() << "/n";
        if(r_buf[1] == 'O' && r_buf[2] == 'K' && r_buf[3] == '!')
            emit sendToMB("Eth_7", "Params were set successfully");
        else emit sendToMB("Eth_8", "Params haven't beet set");
        tcpC->disconnectTcp();
        cs -> updateIP();
        QList<QString> *str_cs = cs->fillList();

        emit sendCurrIp(*str_cs);
        delete str_cs;
    }
        break;
    case setRTC:
        qDebug() << "setRTC" << " r_buf.length: " << r_buf.length() << "/n";
        if(  1 == r_buf[0] && 1 == r_buf[1] && 0 == r_buf[2] && 0 == r_buf[3] &&
           0 == r_buf[4] && 6 == r_buf[5] && 0x10 == r_buf[6] && 0 == r_buf[7] &&
           0 == r_buf[8] && 8 == r_buf[9] && 0 == r_buf[10]  && 3 == r_buf[11]){
            emit sendToMB("Eth_9", "Date, Time were set successfully");
        }
        else emit sendToMB("Eth_10", "Date, Time haven't beet set");
        break;
    default:
//        qDebug() << "default " << "r_buf.length: " << r_buf.length() << "/n";
        emit sendToMB("Eth_11", "Wrong TCP respond.");
        return -1;
    }

    return 0;
}

send_t vmConfigsChat::launchPollTmr(){
    if(!tcpC->isConnected()) {
        tcpC->connectTcp(cs->cnfg.tcpIP, cs->cnfg.tcpPORT);
        delay(2000);
        if(!tcpC->isConnected()) {
            msg_type = connectErr;
            return connectErr;
        }
    }
    QObject::connect(&probePollTmr, &QTimer::timeout, this, &vmConfigsChat::periodReq);
    probePollTmr.setInterval(300);
    probePollTmr.start();
    periodReq();

    return pollTmrStart;
}

send_t vmConfigsChat::getSensorsTransmit(){
    const int getSensors_buf_len = 12;
    QByteArray w_buf(getSensors_buf_len,0);
    w_buf[0] = 1;//Convert.ToByte('G');//Идификатор транзакции
    w_buf[1] = 1;//Идификатор транзакции
    w_buf[2] = 0;//Идификатор протокола
    w_buf[3] = 0;//Идификатор протокола
    w_buf[4] = 0;//Длина
    w_buf[5] = 6;//Длина
    w_buf[6] = 33;//Адрес
    w_buf[7] = 3;//Функциональный код
    w_buf[8] = 0;//Адрес первого регистра
    w_buf[9] = 0;//Адрес первого регистра
    w_buf[10] = 0;
    w_buf[11] = 16;

    if(!tcpC->isConnected()) {
        tcpC->connectTcp(cs->cnfg.tcpIP, cs->cnfg.tcpPORT);
        delay(2000);
        if(!tcpC->isConnected()) {
            msg_type = connectErr;
            return connectErr;
        }
    }
    if(tcpC->sendToTcp(&w_buf) == w_buf.length()) {
        msg_type = getSensors;
        return getSensors;
    }
    msg_type = getSensorsErr;
    return getSensorsErr;
}

send_t vmConfigsChat::setParamsTransmit(){
    const int param_buf_len = 72;
    QByteArray w_buf(param_buf_len,0);
    w_buf[0] = 'G';   //Идификатор транзакции
    w_buf[1] = 'B';   //Идификатор транзакции
    w_buf[2] = 0;     //Идификатор протокола
    w_buf[3] = 0;     //Идификатор протокола
    w_buf[4] = 0;     //Длина
    w_buf[5] = 0x3E;  //Длина
    w_buf[6] = 'A';   //Адрес
    w_buf[7] = 0x10;  //Функциональный код
    w_buf[8] = 0;     //Адрес первого регистра
    w_buf[9] = 0x33;  //Адрес первого регистра
    w_buf[10] = 0;

    cs->fill_buf(w_buf, 11);
    if(!tcpC->isConnected()) {
        tcpC->connectTcp(cs->cnfg.tcpIP, cs->cnfg.tcpPORT);
        delay(2000);
        if(!tcpC->isConnected()) {
            msg_type = connectErr;
            return connectErr;
        }
    }
    if(tcpC->sendToTcp(&w_buf) == w_buf.length()) {
        msg_type = setParams;
        return setParams;
    }
    msg_type = setParamsErr;
    return setParamsErr;
}

send_t vmConfigsChat::setRTCTransmit(){
    const int RTC_mess_len = 19;
    QByteArray w_buf(RTC_mess_len,0);
    QDateTime now = QDateTime::currentDateTime();
    QDate D = now.date();
    QTime T = now.time();
    int temp, temp2; //xf = Convert.ToInt16(xv);     //MessageBox.Show("0x"+GBV.Minute.ToString() + "  " + GBV.Minute.ToString());
    w_buf[0] = 1;//Идификатор транзакции
    w_buf[1] = 1;//Идификатор транзакции
    w_buf[2] = 0;//Идификатор протокола
    w_buf[3] = 0;//Идификатор протокола
    w_buf[4] = 0;//Длина
    w_buf[5] = 0xD;//Длина сообщения
    w_buf[7] = 0x10;//Функциональный код
    w_buf[8] = 0;
    w_buf[9] = 0x8;//Адрес первого регистра Lo байт
    w_buf[10] = 0;
    w_buf[11] = 0x3;//Количество регистров Lo байт
    w_buf[12] = (2 * w_buf[11]);
    temp2 = T.second();
    temp = temp2 / 10;
    w_buf[13] = (temp << 4) + temp2 - temp * 10;
    temp2 = T.minute();
    temp = temp2 / 10;
    w_buf[14] = (temp << 4) + temp2 - temp * 10;
    temp2 = T.hour();
    temp = temp2 / 10;
    w_buf[15] = (temp << 4) + temp2 - temp * 10;
    temp2 = D.day();
    temp = temp2 / 10;
    w_buf[16] = (temp << 4) + temp2 - temp * 10;
    temp2 = D.month();
    temp = temp2 / 10;
    w_buf[17] = (temp << 4) + temp2 - temp * 10 + (D.dayOfWeek()<<5);
    temp2 = D.year() - 2000;
    temp = temp2 / 10;
    w_buf[18] = (temp << 4) + temp2 - temp * 10;

    if(!tcpC->isConnected()) {
        tcpC->connectTcp(cs->cnfg.tcpIP, cs->cnfg.tcpPORT);
        delay(2000);
        if(!tcpC->isConnected()) {
            msg_type = connectErr;
            return connectErr;
        }
    }
    if(tcpC->sendToTcp(&w_buf) == w_buf.length()) {
        msg_type = setRTC;
        return setRTC;
    }
    msg_type = setRTCErr;
    return setRTCErr;
}

void vmConfigsChat::delay(uint t)
{
    QTime dieTime= QTime::currentTime().addMSecs(t);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void vmConfigsChat::pushedButt(QList<QString> ls, qint32 buttNum) {
    if(buttNum >= 0 && buttNum < buttAmount){
        butt = (pushedButt_t)buttNum;
        probePollTmr.stop();
    }
    switch(butt){
        case connectB:
        case periodReqB:
        case setTimeB:
        case setParamsB:
        case getParamsB:
        case loadDeviceB:
        case saveDeviceB:
            if((cs->fillCompareCfg(ls) != 0) || (!tcpC->isConnected()))  {
                if(tcpC->isConnected()) {
                    tcpC->disconnectTcp();
                    return;
                }
                emit sendToMB("TCP", "Attempt to connect");
                tcpC->connectTcp(cs->cnfg.tcpIP, cs->cnfg.tcpPORT);
                return;
            }
            break;
        case disconnectB:
            if(tcpC->isConnected()) {
                tcpC->disconnectTcp();
                return;
            }
            break;
        case saveFileB: cs->fillCompareCfg(ls); break;
        default: break;
    }
    butt_proc();
}

int vmConfigsChat::butt_proc(){
    switch(butt){
        case periodReqB:
          periodReqButt();
          break;
        case connectB:      connectButt(); break;
        case setParamsB:    setParamsButt(); break;
        case getParamsB:    getParamsButt(); break;
        case loadDefaultB:  loadDefaultButt(); break;
        case setTimeB:      setTimeButt(); break;
        case disconnectB:   disconnectButt(); break;
        case loadFileB:     loadFileButt(); break;
        case saveFileB:     saveFileButt(); break;
        default: break;
    }
    butt = noneB;
    return 0;
}

int vmConfigsChat::periodReqButt(){
    tcpC -> setReadyRead_Chart(this);
    QObject::connect(&probePollTmr, &QTimer::timeout, this, &vmConfigsChat::getSensorsTransmit);
    probePollTmr.setInterval(300);
    probePollTmr.start();
    emit sendToMB("TCP", "Poll sensors");
    getSensorsTransmit();
    return 0;
}

int vmConfigsChat::connectButt(){
    qDebug("TCP    Connected");
    emit sendToMB("TCP",    "Connected");
    return 0;
}

void vmConfigsChat::setParamsButt(/*QList<QString> ls*/) {
//    cs->fillCompareCfg(ls);
    setParamsTransmit();
    qDebug("called setParamsButt \n");
    emit sendToMB("TCP",    "Set params");
}

void vmConfigsChat::getParamsButt(/*QString ip_t, QString port_t*/) {
    getParamsTransmit();
    qDebug("get Params \n");
    emit sendToMB("TCP",    "Get params");
}

void vmConfigsChat::loadDefaultButt(/*QList<QString> str*/)
{
    count++;
    cs->cnfg.set_default();
    QList<QString> *str_cs = cs->fillList();
    emit sendCurrIp(*str_cs);
    delete str_cs;
}

int vmConfigsChat::setTimeButt(/*QString ip_t, QString port_t, int t_out*/){
    setRTCTransmit();
    return 0;
}

int vmConfigsChat::disconnectButt(/*QString ip_t, QString port_t*/){
    conn_dir = disconnecting;
//    pointTmr->setTmr(1500,"Attempt to disconnect", disconnecting);
    emit sendToMB("TCP", "Successfully disconnected");
    return 0;
}

void vmConfigsChat::loadFileButt()
{
    count++;
    if(cs->load_file_configs("config.ini") < 0) emit sendErrFileOpen("config.ini");
    QList<QString> *str_cs = cs->fillList();

    emit sendCurrIp(*str_cs);
    emit sendToMB("File",    "Loaded successfully");
    delete str_cs;
}

void vmConfigsChat::saveFileButt(/*QList<QString> ls*/)
{
    count++;
//    cs->fillCompareCfg(ls);
    if(cs->save_file_configs("config.ini") < 0) emit sendErrFileOpen("config.ini");
    else emit sendToMB("File",    "File is saved successfully");
        //emit saveFileSucc("config.ini");
    return;
}
