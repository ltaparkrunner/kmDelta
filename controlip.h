#ifndef CONTROLIP_H
#define CONTROLIP_H

#include <QObject>
#include "mbtcpClient.h"
//#include <string>
#include <QString>
#include "tcp_req.h"

struct avar_t{
    bool alarm;
    uint16_t value;
};

struct chat_data{
    bool sucs;
    avar_t avar[3];
//    double abs[8];
    int32_t abs[8];
    QString T_Date;
    int minute;
    QString st_contr;
    QString vers;
    bool visible;
};

class ControlIp : /*public QObject,*/public tcpMan
{
    Q_OBJECT
public:
//    ControlIp();
//    explicit ControlIp(QObject *parent = 0);
    explicit ControlIp(tcpMan *parent = 0);
//    explicit ControlIp(QObject *parent = 0);


signals:

    void sendToMB(const QString &title, const QString &text);
    void sendToQml(qint16 count);
    void sendToChat(QVariantList abs);
    void sendToDialog(const QString &title);
public slots:
//    void receiveFromQml();
//    void connectButt(std::string ip_t, std::string port_t);
    void connectButt(QString ip_t, QString port_t);
    void periodReqButt(QString ip_t, QString port_t, int t_out);
    void setParamsButt(QString ip_t, QString port_t);
    void getParamsButt(QString ip_t, QString port_t);
    void periodReq(/*QString ip_t, QString port_t*/);
//    void sendMsgButt();

    void displayError(QAbstractSocket::SocketError socketError) override;
    void successConn() override;
    void parseMessage() override;
    int getParamsResp() override;
    int setParamsResp() override;
    int periodReqResp() override;

private:
    int count;
    MbtcpClient* tcpC;
    QTimer tm_tcp_req;
    QString ipt;
    QString portt;
//    QDataStream in_out;
    void respToCondLine(QByteArray rdata, QString title);
    chat_data* periodRespToData(QByteArray rdata);
    int getParamParse(QByteArray dt);
    glob gl;
};

#endif // CONTROLIP_H
