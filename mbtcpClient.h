#ifndef MBTCPCLIENT_H
#define MBTCPCLIENT_H

#include <QDataStream>
#include <QTcpSocket>
#include "ipAddr.h"

QT_BEGIN_NAMESPACE
class QTcpSocket;
QT_END_NAMESPACE

//! [0]
class MbtcpClient : public QObject
{
    Q_OBJECT

public:
    explicit MbtcpClient(QObject *parent = nullptr);

public slots:
    void requestNewFortune();
    void readFortune();
    void displayError(QAbstractSocket::SocketError socketError);

public slots:
    void receiveIpFromQml();
    void commitIpFromQml(QString str);
//    void enableGetFortuneButton();

private:
    int count;
    QTcpSocket *tcpSocket = nullptr;
    QDataStream in;
    QString currentFortune;
    IpAddr ip;
signals:
    void sendToCond1(QString str, bool bl);
    void sendToCond2(QString str1, QString str2);
signals:
    void sendToQml2(QString addr, QString mask, QString port);
};

//! [0]

#endif // MBTCPCLIENT_H
