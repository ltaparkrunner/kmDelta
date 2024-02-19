#ifndef CONFIGS_H
#define CONFIGS_H

//#include <stdint.h>
#include <QString>
//#include "tcp_exch.h"

#include "mbtcpClient.h"

const int n_avar = 4;
const int n_dat = 8;

struct ret_t{
    int res;
    QByteArray *bdata;
};

struct Data
{
    int32_t absolutnoe;
    int32_t smeshenie;
//    Data();
};

struct avar
{
    uchar avariya1_predupregdenie0;
//    uint16_t porog_max;
//    uint16_t porog_min;
    uint16_t porog_max;
    uint16_t porog_min;
    uchar kolvo_avariynih_datchikov;
//    avar();
};

struct parms// : public QObject
{
//    Q_OBJECT
public:
    uchar otnositelnoe_otobragenie;
    bool inversion_data;
    bool inversion_dt;
    avar  avariya[n_avar];
    int porog_max;
    int porog_min;

    uint16_t timeout_alarm;
    uint16_t version_proshivki;
    uint16_t alarmt;
    QString ethIP;
    QString ethIP_extr;  // TODO: what for is this value?
//    QString IP1;
    QString ethIP_new;
    QString ethMASK;
    QString ethMASK_new;

    QString ethPORT;
    QString ethPORT_extr; // TODO: what for is this value?
    QString ethPORT_new;

    Data data[n_dat];
    int32_t mashtab;
    int32_t graph_memory;

    bool obnovlenie_proshivki;
    parms();
};

class configs  //: public QObject
{
    //Q_OBJECT
public:
    explicit configs(MbtcpClient* tcpe);
    ~configs(){}
    int save_file_configs(QString filen = "config.ini");
    int load_file_configs(QString filen = "config.ini");

    int save_eth_configs(tcpIntrfc *cl); // save params to device
    int save_eth_configs_resp(); // respond after save params to device

    int load_eth_configs(tcpIntrfc *cl); // send message to load params from device
    int load_eth_configs_resp(); // respond after load params from device and parsing

//    int save_view_configs(); // save params to view means output to view
//    int load_view_configs(); // load params from view means save to variable cnfg

    int setReadyRead_loadDev(tcpIntrfc *cl);
//    int setReadyRead_saveDev(tcpIntrfc *cl);
//    int setReadyRead_loadChart(tcpIntrfc *cl);
//    parms cnfg;
//    tcp_exch* te;
    QList<QString>* fillList();         //  preparing list to save params to view means output to view
    int fillCfg(QList<QString> &ls);    //  load params from view means save to cnfg variable

private:
    ret_t save_eth_configs_bArray();    // assembly message to save params to device
    ret_t load_eth_configs_bArray();    // assembly message to respond params from device
    bool check_IP(uint8_t ip[], QString& ip_s);
    MbtcpClient* tcpC;
public:
    parms cnfg;
//    tcp_exch* te;
//    bool check_MASK(uint8_t ip[]);
};



#endif // CONFIGS_H

