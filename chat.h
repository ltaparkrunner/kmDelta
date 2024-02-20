#ifndef CHAT_H
#define CHAT_H

#include <QTimer>
#include "mbtcpClient.h"
// установить часы, передать время

class chat : public QObject
{
    Q_OBJECT
public:
    chat();
    int get_tcp_chatdata(MbtcpClient* tcpC); // send message to load params from device
    QList<qint32>* get_tcp_chatdata_resp(MbtcpClient* tcpC); // respond after load params from device and parsing
//    int startTimer();
//    int timerEvent();

private:
//    QTimer probePollTmr;
};

#endif // CHAT_H
