#ifndef CONTROLIP_H
#define CONTROLIP_H

#include <QObject>
#include "mbtcpClient.h"
#include <string>
#include <QString>

class ControlIp : public QObject
{
    Q_OBJECT
public:
//    ControlIp();
//    explicit ControlIp(QObject *parent = 0);
    explicit ControlIp(MbtcpClient &tcpC_, QObject *parent = 0);

signals:
    void sendToQml(int count);
public slots:
//    void receiveFromQml();
//    void connectButt(std::string ip_t, std::string port_t);
    void connectButt(QString ip_t, QString port_t);
    void periodReqButt(QString ip_t, QString port_t, int t_out);
    void setParamsButt(QString ip_t, QString port_t);
    void getParamsButt(QString ip_t, QString port_t);
    void periodReq(/*QString ip_t, QString port_t*/);
//    void sendMsgButt();
private:
    int count;
    MbtcpClient* tcpC;
    QTimer tm_tcp_req;
    QString ipt;
    QString portt;
//    QDataStream in_out;
};

#endif // CONTROLIP_H
