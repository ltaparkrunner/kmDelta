#ifndef CHAT_H
#define CHAT_H

#include <QTimer>
#include "mbtcpClient.h"
#include "configs.h"
// передать время

//struct ret_t{
//    int res;
//    QByteArray *bdata;
//};

const int n_glh = 4;
const int n_vl = 8;
struct glitch
{
    bool alarm;
    uint16_t value;
};
struct value
{
    int32_t absolutnoe;
    int32_t smeshenie;
//    Data();
};
struct probe
{
    glitch glh[n_glh];
    value vl[n_vl];
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
    QList<qint32>* get_tcp_chatdata_resp(MbtcpClient* tcpC); // respond after load params from device and parsing

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
