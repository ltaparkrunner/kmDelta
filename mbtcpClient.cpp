#include <QtNetwork>
#include <QMessageBox>
#include <QDebug>
#include "mbtcpClient.h"



//#include "messbox.h"

//! [0]
MbtcpClient::MbtcpClient(tcpIntrfc *cl, QObject *parent)
    : tcpSocket(new QTcpSocket(this))
//    , ip(new IpAddr(this))
//    , tmr(new QTimer(this))
    , tcpm(cl)
    , cur_ip("192.168.1.170")
    , cur_port("502")
{
//        connect(tcpSocket, &QIODevice::readyRead, this, &MbtcpClient::readFortune);
//        connect(tcpSocket, &QIODevice::readyRead, tcpm, &tcpMan::parseMessage);
//        connect(tcpSocket, &QIODevice::readyRead, tcpm, &tcpMan::periodReqResp);

        connect(tcpSocket, &QAbstractSocket::connected, cl, &tcpIntrfc::successConn);
/*
        typedef void (QAbstractSocket::*QAbstractSocketErrorSignal)(QAbstractSocket::SocketError);

        connect(tcpSocket, static_cast<QAbstractSocketErrorSignal>(&QAbstractSocket::error),
//                this, &MbtcpClient::displayError);
                  tcpm, &tcpIntrfc::displayError);
*/

    typedef void (QAbstractSocket::*QAbstractSocketErrorSignal)(QAbstractSocket::SocketError);
    connect(tcpSocket, static_cast<QAbstractSocketErrorSignal>(&QAbstractSocket::error),
//                this, &MbtcpClient::displayError);
//                  tcpm, &tcpMan::displayError);
        tcpm, &tcpIntrfc::displayError);

//        connect(tcpSocket, &QAbstractSocket::error, tcpm, &tcpIntrfc::displayError);
/*                  */
//            tcpm, &tcpMan::periodReqResp);
}

// void MbtcpClient::successMsg(){
//     emit sendToMB(tr("Fortune Client"), "Success");
// }

bool MbtcpClient::checkConnected(){
    if(tcpSocket->state() == QAbstractSocket::ConnectedState) {
//     emit sendToMB(tr("Fortune Client"), "Success");
     return true;
    }
//    else  emit sendToMB(tr("Fortune Client"), "Can't connect");
    return false;
}

int MbtcpClient::connectTcp(QString &ip_t, QString port_t)
{
//    connect(tcpSocket, &QAbstractSocket::error, tcpm, &tcpIntrfc::displayError);

    qDebug() << "ip_t: " << ip_t << " port_t: " << port_t;
    tcpSocket->abort();
    tcpSocket->connectToHost(ip_t, port_t.toInt());
//    return 0;
//    tmr.singleShot(1000, this, &MbtcpClient::checkConnected);
    return 0;
}

void MbtcpClient::printTcpResp()
{
    if (blockSize == 0) {
       if (tcpSocket->bytesAvailable() < (int)sizeof(quint16))
                return;

     QByteArray rdata = tcpSocket->readAll();
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
//    emit sendToMB(tr("Fortune Client"), QString(mass));
    }
}

int setReadyReadconn() {
    return 0;
}

int MbtcpClient::sendToTcp(QByteArray *bdata){
    if(!checkConnected()){
        return -1;
    }
//    else emit sendToMB(tr("Fortune Client"), tr("Sucessfully connected"));
    return tcpSocket->write(*bdata);
}

int MbtcpClient::onChangeIpPort(QString ip, QString port){
    cur_ip = ip;
    cur_port = port;
    if(tcpSocket->state() == QAbstractSocket::ConnectedState)
        tcpSocket->disconnectFromHost();
    return 0;
}

int MbtcpClient::setReadyRead_loadDev(tcpIntrfc *cl) {
    connect(tcpSocket, &QIODevice::readyRead, cl, &tcpIntrfc::loadDev_Respond);
    return 0;
}

int MbtcpClient::setReadyRead_saveDev(tcpIntrfc *cl) {
    connect(tcpSocket, &QIODevice::readyRead, cl, &tcpIntrfc::saveDev_Respond);
    return 0;
}

int MbtcpClient::setReadyRead_Chart(tcpIntrfc *cl) {
    connect(tcpSocket, &QIODevice::readyRead, cl, &tcpIntrfc::loadChart_Respond);
    return 0;
}
