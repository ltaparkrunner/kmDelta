#ifndef MVCONFIGSCHAT_H
#define MVCONFIGSCHAT_H

#include <QObject>
#include <QString>
#include "tcpIntrfc.h"
#include "configs.h"
#include "chat.h"
#include "pointtimer.h"
//#include "pTmrIntrfc.h"

//#define ba_len 128;
enum send_t{
    nomsg,
    getParams,
    getSensors,
    setParams,
    setRTC,
    pollTmrStart,
    getParamsErr = -1,
    getSensorsErr = -2,
    setParamsErr = -3,
    setRTCErr = -4,
    connectErr = -5
};

class vmConfigsChat : public tcpIntrfc//, public pTmrIntrfc
{
    Q_OBJECT

public:
    explicit vmConfigsChat(configs* cs_, MbtcpClient* tcpC_, tcpIntrfc *parent = 0);
//    void displayError(QAbstractSocket::SocketError socketError) override;
    void displayError() override;
    void successConn() override;
    void successDisconn();
    configs getCs() const;
//    ~vmConfigsChat();
signals:
    void sendToMB(const QString &title, const QString &text);
    void sendToQml(qint16 count);
    void sendToChat(QList<qint32> abs);
    void sendToDialog(const QString &title);
    void sendCurrIp(QList<QString> ls);
    void sendCurrIp_2(const QString &ls);
    void sendErrFileOpen(const QString &title);
    void saveFileSucc(const QString &title);
    void openFileSucc(const QString &title, const QString &text);

public slots:
    int connectButt(QString ip_t, QString port_t);
    int disconnectButt(QString ip_t, QString port_t);
    int periodReqButt(QString ip_t, QString port_t, int t_out);
    int stopReqButt(QString ip_t, QString port_t, int t_out);
    int setTimeButt(QString ip_t, QString port_t, int t_out);
    void setParamsButt(QString ip_t, QString port_t);
    void getParamsButt(QString ip_t, QString port_t);
    void periodReq(/*QString ip_t, QString port_t*/);
//    void loadDevice_readyRead();
//    void saveDevice_readyRead();


    void load_File_Qml();                   // Load_From_File
    void save_File_Qml(QList<QString> ls);  // Save_To_File
    int load_Device_Qml();                  // send message to load params from device
    int save_Device_Qml();                 // save params to device
    int rectCompleted_Qml();
//    void load_Default_Qml(QString str);
    void load_Default_Qml(QList<QString> str);
    void commitFromQml(QString str);
    void expired_Respond();

    int loadDev_Respond() override;    // receive device's respond after send message to load params from device
    int saveDev_Respond() override;    // receive device's respond after send message tosave params to device
    int loadChart_Respond() override;

    int timeout_Respond() override;

//    int tmrAddPoint();
private:
    int count;
    configs* cs;
    MbtcpClient* tcpC;
    QTimer probePollTmr;
//   QTimer pointTmr;
    pointTimer* pointTmr;
    chat* cht;
    send_t msg_type;
    dir_t conn_dir;
//    QByteArray w_buf;
//    QString strPointTmr;
//    QVariant np;
    void sendMess();
    send_t getParamsTransmit();
    int tcpDevRespond();
    send_t launchPollTmr();
    send_t getSensorsTransmit();
    send_t setParamsTransmit();
    send_t setRTCTransmit();
    void delay(uint);
    int sensorsResp(QByteArray r_buf);

};

#endif // MVCONFIGSCHAT_H
