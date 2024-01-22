#include <QtNetwork>
#include <QMessageBox>
#include <QDebug>
#include "mbtcpClient.h"


//#include "messbox.h"

//! [0]
//mbtcpClient::mbtcpClient(QObject  *parent)
MbtcpClient::MbtcpClient(QObject *parent)
    : tcpSocket(new QTcpSocket(this))
    , ip(new IpAddr(this))
    , tmr(new QTimer(this))
{
    //! [1]
//        in_out.setDevice(tcpSocket);
        //in_out.setVersion(QDataStream::Qt_4_0);
//        in_out.setVersion(QDataStream::Qt_5_6);
    //! [1]
    //! [2]
        //qwp = qwp_;
        connect(tcpSocket, &QIODevice::readyRead, this, &MbtcpClient::readFortune);
        connect(tcpSocket, &QAbstractSocket::connected, this, &MbtcpClient::successMsg);
//        connect(tcpSocket, &QAbstractSocket::disconnected, this, &MbtcpClient::unsuccessMsg);
//        connect(tcpSocket, &QAbstractSocket::disconnected, this, &MbtcpClient::unsuccessMsg);
//        connect(tcpSocket, &QAbstractSocket::errorOccurred,
        typedef void (QAbstractSocket::*QAbstractSocketErrorSignal)(QAbstractSocket::SocketError);
        connect(tcpSocket, static_cast<QAbstractSocketErrorSignal>(&QAbstractSocket::error),
                this, &MbtcpClient::displayError);
     //! [2]
}
void MbtcpClient::successMsg(){
    emit sendToMB(tr("Fortune Client"), "Success");
}
int MbtcpClient::checkConnected(){
    if(tcpSocket->state() == QAbstractSocket::ConnectedState) {
     emit sendToMB(tr("Fortune Client"), "Success");
     return 0;
    }
    else  emit sendToMB(tr("Fortune Client"), "Can't connect");
    return -1;
}

//void MbtcpClient::requestNewFortune(std::string ip_t, std::string port_t)
void MbtcpClient::requestNewFortune(QString ip_t, QString port_t)
{
    // before connection
//    in_out.setDevice(tcpSocket);
//    in_out.setVersion(QDataStream::Qt_5_12);
    tcpSocket->abort();
//! [7]
    //QHostAddress Addr(ip.ip_addr);get_ip()
    //tcpSocket->connectToHost("en.wikipedia.org", 443);
//    auto obj = this->parent()->findChild<QObject>("viewer");
//    qDebug(obj.findChild("main1").toString());
//    auto obj = this->parent();
//    qDebug(obj->toString());
    //auto obj2 = this->parent()->children()
    tcpSocket->connectToHost(ip_t, port_t.toInt());
//    tcpSocket->connectToHost(ip.get_ip(), ip.get_port());
                //hostCombo->currentText(), portLineEdit->text().toInt());
    tmr.singleShot(1000, this, &MbtcpClient::checkConnected);
//    tmr.setInterval(1000);
//    tmr.start();

//! [7]
}

//! [8]
void MbtcpClient::readFortune()
{
/*
    in.startTransaction();

    QString nextFortune;
    in >> nextFortune;

    if (!in.commitTransaction())
        return;

    if (nextFortune == currentFortune) {
        QTimer::singleShot(0, this, &mbtcpClient::requestNewFortune);
        return;
    }

    currentFortune = nextFortune;
    statusLabel->setText(currentFortune);
    getFortuneButton->setEnabled(true);
*/
//! [9]
    //QDataStream in(tcpSocket);
    //in.setVersion(QDataStream::Qt_4_0);
    //in_out.setVersion(QDataStream::Qt_5_6);

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

//! [8]
    emit sendToMB(tr("Fortune Client"), QString(mass));
//! [10]
//        in_out >> blockSize;
    }

//    if (tcpSocket->bytesAvailable() < blockSize)
//        return;
//! [10] //! [11]

//    QString nextFortune;
//    in >> nextFortune;
//    in_out >> answer;
//    if (nextFortune == currentFortune) {
//        QTimer::singleShot(0, this, &MbtcpClient::requestNewFortune);
//        return;
//    }
//! [11]

//! [12]
//    currentFortune = nextFortune;
//! [9]
    //statusLabel->setText(currentFortune);
    //getFortuneButton->setEnabled(true);
}
//! [8]

//! [13]
void MbtcpClient::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
    /*
        QMessageBox::information(this, tr("Fortune Client"),
                                 tr("The host was not found. Please check the "
                                    "host name and port settings."));
    */
        emit sendToMB(tr("Fortune Client"), tr("The host was not found. Please check the "
                                               "host name and port settings."));
        break;
    case QAbstractSocket::ConnectionRefusedError:
    /*
        QMessageBox::information(this, tr("Fortune Client"),
                                 tr("The connection was refused by the peer. "
                                    "Make sure the fortune server is running, "
                                    "and check that the host name and port "
                                    "settings are correct."));
    */
        emit sendToMB(tr("Fortune Client"), tr("The connection was refused by the peer. "
                                               "Make sure the fortune server is running, "
                                               "and check that the host name and port "
                                               "settings are correct."));
        break;
    default:
    /*
        QMessageBox::information(this, tr("Fortune Client"),
                                 tr("The following error occurred: %1.")
                                 .arg(tcpSocket->errorString()));
    */
        emit sendToMB(tr("Fortune Client"), tr("The following error occurred: %1.")
                      .arg(tcpSocket->errorString()));
    }

    //getFortuneButton->setEnabled(true);
}

void MbtcpClient::receiveIpFromQml()
{
    count++;
    emit sendToQml2(ip.get_ip2(), ip.get_mask2(), ip.get_port2());
}
void MbtcpClient::commitIpFromQml(QString str)
{
    str.append("for");
    emit sendToQml2(str, ip.get_mask2(), ip.get_port2());
    //messageDialog
}

int MbtcpClient::request() {
    if(checkConnected() < 0){
        return -1;
    }
    else emit sendToMB(tr("Fortune Client"), tr("Sucessfully connected"));
    const char data[12] = {0x47, 0x42, 0,0,0,6,0x41,3,0,0x33,0,0};
    return tcpSocket->write(QByteArray(data,12));
}

int MbtcpClient::setParam(QString ip_t, QString port_t, QByteArray mess) {
    if(checkConnected() < 0){
        return -1;
    }
    else emit sendToMB(tr("Fortune Client"), tr("Sucessfully connected"));
    const char data[12] = {0x47, 0x42, 0,0,0,6,0x41,3,0,0x33,0,0};
    return tcpSocket->write(QByteArray(data,12));
}

int MbtcpClient::periodReq() {
    if(checkConnected() < 0){
        return -1;
    }
    else emit sendToMB(tr("Fortune Client"), tr("Sucessfully connected"));
    const char data[12] = {0x47, 0x42, 0,0,0,6,0x41,3,0,0x33,0,0};
    return tcpSocket->write(QByteArray(data,12));
}


int MbtcpClient::request2(QByteArray &bdata){
    if(checkConnected() < 0){
        return -1;
    }
    else sendToMB(tr("Fortune Client"), tr("Sucessfully connected"));
    //if(!tcpSocket->isOpen()) return -1;
    //const char data[12] = {0x47, 0x42, 0,0,0,6,0x41,3,0,0x33,0,0};
    return tcpSocket->write(bdata);
//        in_out.startTransaction();

//        in_out << request;
//    return 0;
//    if (!in_out.commitTransaction())
//        return;


//    in_out >> answer;
//    return;
}


//! [13]

//! [0]
