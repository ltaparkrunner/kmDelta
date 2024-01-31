#include "controlip.h"
//#include "crc32.h"
#include "tcp_req.h"
#include<QDebug>
#include <QObject>
#include <exception>

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

 void ControlIp::displayError(QAbstractSocket::SocketError socketError){
    qDebug("displayError non-virtual func");
    //int32_t abs[8];
    QVariantList abs;
    for(int i = 0; i<4; i++) {
        abs.append(10); abs.append(5);
    }

    emit sendToChat(abs);
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        emit sendToMB(tr("Fortune Client"), tr("The host was not found. Please check the "
                                               "host name and port settings."));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        emit sendToMB(tr("Fortune Client"), tr("The connection was refused by the peer. "
                                               "Make sure the fortune server is running, "
                                               "and check that the host name and port "
                                               "settings are correct."));
        break;
    default:
        emit sendToMB(tr("Fortune Client"), tr("The following error occurred: %1.")
//                      .arg(tcpC -> tcpSocket->errorString()));
                      .arg(tcpC ->getErrString()));
    }
 }

 void ControlIp::successConn(){
     qDebug("successConn non-virtual func");
     emit sendToMB(tr("Fortune Client"), "Success");
     int32_t abs[8];
     for(int i = 0; i<8; i++) abs[i] = 10;
//     emit sendToChat(abs);
 }

 void ControlIp::parseMessage(){
     qDebug("parseMessage non-virtual func");
 }

int ControlIp::getParamsResp(){
     qDebug("getParamsResp non-virtual func");
     if (tcpC ->getBlSz() == 0) {
        if (tcpC -> getBAvl() < (int)sizeof(quint16))
                 return 0;

         QByteArray rdata = tcpC ->getAll();
         char mass[64*3 + 5] = {0};
         char mass2[ ] = "     ";
         int indx = 0;

         for(auto i = rdata.begin(); i != rdata.end(); i++){
              sprintf(mass2, " %02x",static_cast<uchar>(*i));
              mass[indx++] = mass2[0];
              mass[indx++] = mass2[1];
              mass[indx++] = mass2[2];
         }
         mass[indx++] = 0;

         qDebug("on_read string: 0x%s", mass);
         emit sendToMB(tr("Fortune Client"), QString(mass));
     }
     return 2;
}

int ControlIp::setParamsResp() {
     qDebug("setParamsResp non-virtual func");
     if (tcpC ->getBlSz() == 0) {
        if (tcpC -> getBAvl() < (int)sizeof(quint16))
                 return 0;

         QByteArray rdata = tcpC ->getAll();
         char mass[64*3 + 5] = {0};
         char mass2[ ] = "     ";
         int indx = 0;

         for(auto i = rdata.begin(); i != rdata.end(); i++){
             sprintf(mass2, " %02x",static_cast<uchar>(*i));
             mass[indx++] = mass2[0];
             mass[indx++] = mass2[1];
             mass[indx++] = mass2[2];
         }
         mass[indx++] = 0;
         qDebug("on_read string: 0x%s", mass);
         emit sendToMB(tr("Fortune Client"), QString(mass));
     }
     return 2;
}

int ControlIp::periodReqResp(){
    qDebug("periodReqResp non-virtual func");
    if (tcpC ->getBlSz() == 0) {
       if (tcpC -> getBAvl() < (int)sizeof(quint16))
                return 0;

        QByteArray rdata = tcpC ->getAll();
        chat_data* chat_d = periodRespToData(rdata);
        for(int i = 0; i<8; i++) chat_d->abs[i] = 10;
//        emit sendToChat(chat_d->abs);
    }
    return 2;
}

void ControlIp::respToCondLine(QByteArray rdata) {
    char mass[64*3 + 5] = {0};
    char mass2[ ] = "     ";
    int indx = 0;

    for(auto i = rdata.begin(); i != rdata.end(); i++){
        sprintf(mass2, " %02x",static_cast<uchar>(*i));
        mass[indx++] = mass2[0];
        mass[indx++] = mass2[1];
        mass[indx++] = mass2[2];
    }
    mass[indx++] = 0;

    qDebug("on_read string: 0x%s", mass);
    emit sendToMB(tr("Fortune Client"), QString(mass));
}

chat_data* ControlIp::periodRespToData(QByteArray dt) {
    chat_data *cd = new chat_data();
    cd->sucs = false;
    try {
        if(dt.length() >= 35) {
            int nr = 9;//9 - начало данных
            for (int i = 0; i < 8; i++) {
                uint d = dt[nr];
                d = d << 8; nr++;
                d = d | dt[nr]; nr++;
                int16_t id = (int16_t)d;
                if (d == 0x8000) {
                    cd->abs[i] = -20000;
                }
                else {
                    cd->abs[i] = id;    // / 2.0;
        //            GL.data[i].absolutnoe = dd;
                }
            }
            if (0 != dt[32] ) { cd->avar[0].alarm = true; cd->avar[0].value = dt[32]; }
            else { cd->avar[0].alarm = false; cd->avar[0].value = 0; }
            if (0 != dt[33]) { cd->avar[1].alarm = true; cd->avar[1].value = dt[33]; }
            else { cd->avar[1].alarm = false; cd->avar[1].value = 0; }//Неисправность МКЛП
            if (0 != dt[34]) { cd->avar[2].alarm = true; cd->avar[2].value = dt[34]; }
            else { cd->avar[2].alarm = false; cd->avar[2].value = 0; }//Нет_связи_с МКЛП

            if (0 != dt[28] && 0 != dt[29])///Дата и время
            {
                QString x[5];   // = new QString[5];
                for (int16_t h = 0; h < 5; h++) { x[h] = QString::number(dt[25 + h],10); if (x[h].length() == 1) x[h] = "0" + x[h]; }
                cd->T_Date = x[2] + ":" + x[1] + ":" + x[0] + " " + x[3] + "." + x[4] + ".20" + QString::number(dt[30]);
            }
            cd->sucs = true;
        }
        if(dt.length() >= 45) {
            cd->minute = (dt[35] << 8) + dt[36]; cd->visible = true;
            if (1 == dt[38])
            {
                cd->st_contr = "Алгоритм текущего мониторинга мёртвого нуля: ";
            }
            if (3 == dt[38])
            {
                cd->st_contr = "Алгоритм калибровки: ";
            }
            uint32_t CheckSum = (uint32_t)dt[41] << 24 | (uint32_t)dt[42] << 16 | (uint32_t)dt[43] << 8 | (uint32_t)dt[44];
            if (CheckSum != 0)
                cd->vers = " Версия: " + QString::number(dt[40])+ "(CRC32: " + QString::number(CheckSum, 16) + ")";
            else
                cd->vers = " Версия: " + QString::number(dt[40]);
        }
        else cd->visible = false;
    }
    catch(std::runtime_error ex) {
        qDebug("Exception", ex.what());
    }
    return cd;
}
