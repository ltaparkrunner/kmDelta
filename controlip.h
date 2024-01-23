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
    void periodReqButt(QString ip_t, QString port_t);
    void setParamButt(QString ip_t, QString port_t);
    void requestParamsButt();
//    void sendMsgButt();
private:
    int count;
    MbtcpClient* tcpC;
//    QDataStream in_out;
};

#endif // CONTROLIP_H
