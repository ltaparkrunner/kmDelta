#ifndef IPADDR_H
#define IPADDR_H

#include <QObject>
#include <QHostAddress>

class IpAddr : public QObject
{
    Q_OBJECT
public:
//    ControlIp();
    explicit IpAddr(QObject *parent = 0);
    void init();
signals:
    void sendToQml2(QString addr, QString mask, QString port);
public slots:
    void receiveFromQml();
    void commitFromQml(QString str);
public:
    QHostAddress get_ip();
    quint16 get_port();
private:
    int count;
    QString ip_addr;
    QString ip_mask;
    QString port;
};

#endif // IPADDR_H
