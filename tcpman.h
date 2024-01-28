#ifndef TCPMAN_H
#define TCPMAN_H

#include <QObject>
#include <QTcpSocket>
#include <QByteArray>
#include <QString>

class tcpMan : public QObject
{
    Q_OBJECT
public:
    tcpMan(QObject *parent) : QObject(parent){}
//    tcpMan(QObject *parent) : QObject(parent){};
public slots:
    // virtual void displayError(QAbstractSocket::SocketError socketError);
    // virtual void successConn();
    // virtual void parseMessage();
    // virtual void getParamsResp();
    // virtual void setParamsResp();
    virtual void periodReqResp();
    //void periodReqResp(){}
//private:
//    tcpMan();
};

#endif // TCPMAN_H
