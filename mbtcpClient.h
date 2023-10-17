#ifndef MBTCPCLIENT_H
#define MBTCPCLIENT_H

#include <QDataStream>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
class QTcpSocket;
QT_END_NAMESPACE

//! [0]
class mbtcpClient : public QObject
{
    Q_OBJECT

public:
    explicit mbtcpClient(QObject *parent = nullptr);

private slots:
    void requestNewFortune();
    void readFortune();
    void displayError(QAbstractSocket::SocketError socketError);
    void enableGetFortuneButton();


    QTcpSocket *tcpSocket = nullptr;
    QDataStream in;
    QString currentFortune;
};
//! [0]

#endif // MBTCPCLIENT_H
