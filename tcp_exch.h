#ifndef TCP_EXCH_H
#define TCP_EXCH_H

#include <QTcpSocket>
#include "ipAddr.h"
#include "tcpman.h"

class tcp_exch: public QObject
{
    Q_OBJECT

public:
    explicit tcp_exch(tcpMan *tm, QObject *parent = nullptr);
    int getCond();
    int connect(QString &ip, QString &port);
    void finishConn();
    int sendMess(QByteArray ba);

    QByteArray& receiveMess();

private:
    QTcpSocket *tcpSocket = nullptr;
    IpAddr ip;
    tcpMan *tcpm;
    int condition;
};

#endif // TCP_EXCH_H
