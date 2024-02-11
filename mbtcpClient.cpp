#include <QtNetwork>
#include <QMessageBox>
#include <QDebug>
#include "mbtcpClient.h"



//#include "messbox.h"

//! [0]
MbtcpClient::MbtcpClient(/*tcpMan *tm,*/ QObject *parent)
    : tcpSocket(new QTcpSocket(this))
    , ip(new IpAddr(this))
//    , tmr(new QTimer(this))
    , tcpm(nullptr)
{
//        connect(tcpSocket, &QIODevice::readyRead, this, &MbtcpClient::readFortune);
//        connect(tcpSocket, &QIODevice::readyRead, tcpm, &tcpMan::parseMessage);
//        connect(tcpSocket, &QIODevice::readyRead, tcpm, &tcpMan::periodReqResp);
/*
        connect(tcpSocket, &QAbstractSocket::connected, tcpm, &tcpMan::successConn);
        typedef void (QAbstractSocket::*QAbstractSocketErrorSignal)(QAbstractSocket::SocketError);
        connect(tcpSocket, static_cast<QAbstractSocketErrorSignal>(&QAbstractSocket::error),
*/
//                this, &MbtcpClient::displayError);
/*                  tcpm, &tcpMan::displayError);
 *                  */
//            tcpm, &tcpMan::periodReqResp);
}

// void MbtcpClient::successMsg(){
//     emit sendToMB(tr("Fortune Client"), "Success");
// }

int MbtcpClient::checkConnected(){
    if(tcpSocket->state() == QAbstractSocket::ConnectedState) {
//     emit sendToMB(tr("Fortune Client"), "Success");
     return 0;
    }
//    else  emit sendToMB(tr("Fortune Client"), "Can't connect");
    return -1;
}

void MbtcpClient::connectTcp(QString ip_t, QString port_t)
{
    tcpSocket->abort();
    tcpSocket->connectToHost(ip_t, port_t.toInt());

//    tmr.singleShot(1000, this, &MbtcpClient::checkConnected);
}

void MbtcpClient::readFortune()
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

// void MbtcpClient::displayError(QAbstractSocket::SocketError socketError)
// {
//     switch (socketError) {
//     case QAbstractSocket::RemoteHostClosedError:
//         break;
//     case QAbstractSocket::HostNotFoundError:
//         emit sendToMB(tr("Km_Delta_connection"), tr("The host was not found. Please check the "
//                                                "host name and port settings."));
//         break;
//     case QAbstractSocket::ConnectionRefusedError:
//         emit sendToMB(tr("Km_Delta_connection"), tr("The connection was refused by the peer. "
//                                                "Make sure the fortune server is running, "
//                                                "and check that the host name and port "
//                                                "settings are correct."));
//         break;
//     default:
//         emit sendToMB(tr("Km_Delta_connection"), tr("The following error occurred: %1.")
//                       .arg(tcpSocket->errorString()));
//     }
// }

// void MbtcpClient::receiveIpFromQml()
// {
//     count++;
//     emit sendToQml2(ip.get_ip2(), ip.get_mask2(), ip.get_port2());
// }

// void MbtcpClient::commitIpFromQml(QString str)
// {
//     str.append("for");
//     emit sendToQml2(str, ip.get_mask2(), ip.get_port2());
//     //messageDialog
// }

//int MbtcpClient::request() {
//    return 0;
//}

// int MbtcpClient::getParams(QString ip_t, QString port_t, QByteArray mess) {
//     if(checkConnected() < 0){
//         return -1;
//     }
//     else emit sendToMB(tr("Fortune Client"), tr("Sucessfully connected"));
//     connect(tcpSocket, &QIODevice::readyRead, tcpm, &tcpMan::getParamsResp);
//     return tcpSocket->write(mess);
// }

// int MbtcpClient::setParams(QString ip_t, QString port_t, QByteArray mess) {
//     if(checkConnected() < 0){
//         return -1;
//     }
//     else emit sendToMB(tr("Fortune Client"), tr("Sucessfully connected"));
//     connect(tcpSocket, &QIODevice::readyRead, tcpm, &tcpMan::setParamsResp);
//     return tcpSocket->write(mess);
// }

// int MbtcpClient::periodReq(QString ip_t, QString port_t, QByteArray mess) {
//     if(checkConnected() < 0){
//         return -1;
//     }
//     else emit sendToMB(tr("Fortune Client"), tr("Sucessfully connected"));
//     connect(tcpSocket, &QIODevice::readyRead, tcpm, &tcpMan::periodReqResp);
//     return tcpSocket->write(mess);
// }

int setReadyReadconn() {

}

int MbtcpClient::sendToTcp(QByteArray &bdata){
    if(checkConnected() < 0){
        return -1;
    }
//    else emit sendToMB(tr("Fortune Client"), tr("Sucessfully connected"));
    return tcpSocket->write(bdata);
}
