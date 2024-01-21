#ifndef TCP_REQ_H
#define TCP_REQ_H

#include <QObject>

const int n_avar = 4;
const int n_dat = 8;

struct Data
{
    double absolutnoe;
    double smeshenie;
    Data();
};

struct avar
{
    uchar avariya1_predupregdenie0;
//    uint16_t porog_max;
//    uint16_t porog_min;
    uint16_t porog_max;
    uint16_t porog_min;
    uchar kolvo_avariynih_datchikov;
    avar();
};
struct ret_t{
    int res;
    QByteArray *bdata;
};

struct glob
{
    uchar otnositelnoe_otobragenie;
    bool inversion_data;
    avar  avariya[n_avar];
    int porog_max;
    int porog_min;
    uint16_t timeout_alarm;
    uint16_t version_proshivki;
    uint16_t alarmt;
    QString IP;
    QString IP_new;
    QString MASK;
//    uint16_t  DPORT;
    QString DPORT;
    QString DPORT_new;

    Data data[n_dat];
    bool check_IP(uint8_t ip[]);
    bool check_MASK(uint8_t ip[]);
    glob();
//    uint32_t crc32(QByteArray m);
};

class tcp_req
{
public:
    tcp_req();
    ret_t tcp_req_init();
private:

};

#endif // TCP_REQ_H
