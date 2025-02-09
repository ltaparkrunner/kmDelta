#ifndef CHAT_H
#define CHAT_H

#include "mbtcpClient.h"
#include "configs.h"

const int n_glh = 4;
const int n_vl = 8;
struct glitch
{
    bool alarm;
    uint16_t value;
};
struct val
{
    int32_t absolutnoe;
    int32_t smeshenie;
//    Data();
};
struct probe
{
    glitch glh[n_glh];
    val vl[n_vl];
};

struct label_vniim {
    bool Visible;
    QString Text;
};

class chat // : public QObject
{
//    Q_OBJECT
public:
    explicit chat();
    int get_tcp_chatdata(MbtcpClient* tcpC); // send message to load params from device
    QList<qint32>& parse_tcp_resp(QByteArray &buf); // respond after load params from device and parsing

private:
    ret_t get_tcp_chatdata_bArray();
    probe prb;
    QString T_Date;
    int minute;
    QString status_control;
    label_vniim lvm;
    uint32_t CheckSum;
};

#endif // CHAT_H
