#ifndef TCPINTRFS_H
#define TCPINTRFS_H

#include <QObject>
#include <QTcpSocket>
#include <QByteArray>
#include <QString>

//typedef


class tcpIntrfc : public QObject
{
    Q_OBJECT
public:
    tcpIntrfc(QObject *parent) : QObject(parent){}
public slots:
    virtual void displayError(QAbstractSocket::SocketError socketError) = 0;    // Error message
    virtual void successConn() = 0;                                             // Success connection
    virtual void loadDev_readyRead() = 0;
    virtual void saveDev_readyRead() = 0;
    virtual void loadChart_readyRead() = 0;
//    virtual void parseMessage() = 0;
//    virtual int getParamsResp() = 0;
//    virtual int setParamsResp() = 0;
//    virtual int periodReqResp() = 0;
    //void periodReqResp(){}
//private:
//    tcpMan();
};
//using fp = void (tcpIntrfc::*)();
using fp = void (*)();
#endif // TCPINTRFS_H
