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
    virtual void displayError(QAbstractSocket::SocketError socketError) = 0;    // Error message
    virtual void successConn() = 0;                                             // Success connection
//    virtual void parseMessage() = 0;
//    virtual int getParamsResp() = 0;
//    virtual int setParamsResp() = 0;
//    virtual int periodReqResp() = 0;
    //void periodReqResp(){}
//private:
//    tcpMan();
};

#endif // TCPMAN_H
