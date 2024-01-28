#ifndef MBTCPCLIENT_H
#define MBTCPCLIENT_H

#include <QDataStream>
#include <QTcpSocket>
#include <QtQuick/QQuickView>
#include <QTimer>
//#include <string>
#include <QString>

#include "ipAddr.h"
#include "tcpman.h"

QT_BEGIN_NAMESPACE
class QTcpSocket;
QT_END_NAMESPACE

//! [0]
class MbtcpClient : public QObject
{
    Q_OBJECT

public:
//    explicit MbtcpClient(QObject *parent = nullptr);
    explicit MbtcpClient(tcpMan *tm, QObject *parent = nullptr);
//    void requestNewFortune(std::string ip_t, std::string port_t);
    void requestNewFortune(QString ip_t, QString port_t);
public slots:

    void readFortune();
    void displayError(QAbstractSocket::SocketError socketError);
    void successMsg();
    int checkConnected();

    int getParamsResp();
    int setParamsResp();
    int periodReqResp();

//    void enableGetFortuneButton();

public slots:
    void receiveIpFromQml();
    void commitIpFromQml(QString str);
    int request();
    int request2(QByteArray &bdata);
    int setParams(QString ip_t, QString port_t, QByteArray mess);
    int getParams(QString ip_t, QString port_t, QByteArray mess);
    int periodReq(QString ip_t, QString port_t, QByteArray mess);


signals:
    void sendToMB(const QString &title, const QString &text);
    //void sendToMB(QString &title, QString &text);

private:
    QTcpSocket *tcpSocket = nullptr;
    IpAddr ip;
    QTimer tmr;
    tcpMan *tcpm;
//    QDataStream in_out;
//    QDataStream in;
//    QDataStream out;
    QString currentFortune;
    quint16 blockSize;
    int count;
    QByteArray answer;
    //QQuickView* qwp;
    int (*func)(QByteArray &barr);
    // int(*TEST(TestSuite, TestName)
    //     {

    //     }
    //     )

signals:
    void sendToCond1(QString str, bool bl);
    void sendToCond2(QString str1, QString str2);
    void sendToQml2(QString addr, QString mask, QString port);
};

//! [0]

#endif // MBTCPCLIENT_H
