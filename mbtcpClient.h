#ifndef MBTCPCLIENT_H
#define MBTCPCLIENT_H

#include <QDataStream>
#include <QTcpSocket>
#include <QtQuick/QQuickView>
#include <QTimer>
//#include <string>
#include <QString>

//#include "ipAddr.h"
#include "tcpIntrfc.h"

QT_BEGIN_NAMESPACE
class QTcpSocket;
QT_END_NAMESPACE

class MbtcpClient : public QObject
{
    Q_OBJECT
public:
    explicit MbtcpClient(tcpIntrfc *cl, QObject *parent = nullptr);

    int connectTcp(QString &ip_t, QString port_t);
 //   bool isConnected();
    QString getErrString(){
        return tcpSocket->errorString();
    }
    quint16 getBlSz(){return blockSize;}
    int  getBAvl(){return tcpSocket->bytesAvailable();}
    QByteArray getAll(){return tcpSocket->readAll();}
    int setReadyRead_loadDev(tcpIntrfc *cl);
    int setReadyRead_saveDev(tcpIntrfc *cl);
    int setReadyRead_Chart(tcpIntrfc *cl);
    int setEventsSlot();
public slots:

    void printTcpResp();
    bool checkConnected();
    int sendToTcp(QByteArray *bdata);
    int onChangeIpPort(QString ip, QString port);

private:
    QTcpSocket *tcpSocket = nullptr;

    tcpIntrfc *tcpm;
    quint16 blockSize;
    QByteArray answer;

    QString cur_ip;
    QString cur_port;
};

#endif // MBTCPCLIENT_H
