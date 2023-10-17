#include <QtNetwork>
#include <QMessageBox>

#include "mbtcpClient.h"

//! [0]
mbtcpClient::mbtcpClient(QObject  *parent)
    : tcpSocket(new QTcpSocket(this))
{
    //! [1]
        in.setDevice(tcpSocket);
        in.setVersion(QDataStream::Qt_4_0);
    //! [1]
    //! [2]

        connect(tcpSocket, &QIODevice::readyRead, this, &mbtcpClient::readFortune);

        connect(tcpSocket, &QAbstractSocket::errorOccurred,

                this, &mbtcpClient::displayError);
     //! [2]
}

void mbtcpClient::requestNewFortune()
{
    // before connection
    tcpSocket->abort();
//! [7]
    tcpSocket->connectToHost(hostCombo->currentText(),
                             portLineEdit->text().toInt());
//! [7]
}

//! [8]
void mbtcpClient::readFortune()
{
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
}
//! [8]

//! [13]
void mbtcpClient::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this, tr("Fortune Client"),
                                 tr("The host was not found. Please check the "
                                    "host name and port settings."));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this, tr("Fortune Client"),
                                 tr("The connection was refused by the peer. "
                                    "Make sure the fortune server is running, "
                                    "and check that the host name and port "
                                    "settings are correct."));
        break;
    default:
        QMessageBox::information(this, tr("Fortune Client"),
                                 tr("The following error occurred: %1.")
                                 .arg(tcpSocket->errorString()));
    }

    //getFortuneButton->setEnabled(true);
}
//! [13]

//! [0]
