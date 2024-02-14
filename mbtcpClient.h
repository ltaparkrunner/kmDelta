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

class MbtcpClient : public QObject
{
    Q_OBJECT

public:
    explicit MbtcpClient(QObject *parent = nullptr);

    int connectTcp(QString ip_t, QString port_t);
    QString getErrString(){return tcpSocket->errorString();}
    quint16 getBlSz(){return blockSize;}
    int  getBAvl(){return tcpSocket->bytesAvailable();}
    QByteArray getAll(){return tcpSocket->readAll();}
    int setReadyReadSlot();
    int setEventsSlot();
public slots:

    void printTcpResp();
    int checkConnected();
    int sendToTcp(QByteArray &bdata);
    int onChangeIpPort(QString ip, QString port);

private:
    QTcpSocket *tcpSocket;

    tcpMan *tcpm;
    quint16 blockSize;
    QByteArray answer;

    QString cur_ip;
    QString cur_port;
};

#endif // MBTCPCLIENT_H
