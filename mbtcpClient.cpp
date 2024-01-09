#include <QtNetwork>
#include <QMessageBox>

#include "mbtcpClient.h"

//! [0]
MbtcpClient::MbtcpClient(QObject  *parent)
    : tcpSocket(new QTcpSocket(this))
    , ip(new IpAddr())
{
    //! [1]
        in.setDevice(tcpSocket);
        in.setVersion(QDataStream::Qt_4_0);
    //! [1]
    //! [2]

        connect(tcpSocket, &QIODevice::readyRead, this, &MbtcpClient::readFortune);

        connect(tcpSocket, &QAbstractSocket::errorOccurred,

                this, &MbtcpClient::displayError);
     //! [2]
}

void MbtcpClient::requestNewFortune()
{
    // before connection
    tcpSocket->abort();
//! [7]
    tcpSocket->connectToHost(ip.get_ip(), ip.get_port());
//! [7]
}

//! [8]
void MbtcpClient::readFortune()
{
    in.startTransaction();

    QString nextFortune;
    in >> nextFortune;

    if (!in.commitTransaction())
        return;

    if (nextFortune == currentFortune) {
        QTimer::singleShot(0, this, &MbtcpClient::requestNewFortune);
        return;
    }

    currentFortune = nextFortune;
    emit sendToCond1("count", true);
    //statusLabel->setText(currentFortune);
    //getFortuneButton->setEnabled(true);
}
//! [8]

//! [13]
//!

void MbtcpClient::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        // QMessageBox::information(this, tr("Fortune Client"),
        //                          tr("The host was not found. Please check the "
        //                             "host name and port settings."));
        emit sendToCond2(tr("Fortune Client"), tr("The host was not found. Please check the "
                                     "host name and port settings."));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        // QMessageBox::information(this, tr("Fortune Client"),
        //                          tr("The connection was refused by the peer. "
        //                             "Make sure the fortune server is running, "
        //                             "and check that the host name and port "
        //                             "settings are correct."));
        emit sendToCond2(tr("Fortune Client"), tr("The connection was refused by the peer. "
                                     "Make sure the fortune server is running, "
                                     "and check that the host name and port "
                                     "settings are correct."));
        break;
    default:
        // QMessageBox::information(this, tr("Fortune Client"),
        //                          tr("The following error occurred: %1.")
        //                          .arg(tcpSocket->errorString()));
        emit sendToCond2(tr("Fortune Client"), tr("The following error occurred: %1.").arg(tcpSocket->errorString()));
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

//! [13]

//! [0]
