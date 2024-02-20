#ifndef MVCONFIGSCHAT_H
#define MVCONFIGSCHAT_H

#include <QObject>
#include <QString>
#include "tcpIntrfc.h"
#include "configs.h"
#include "chat.h"

class vmConfigsChat : public tcpIntrfc
{
    Q_OBJECT

public:
    explicit vmConfigsChat(configs* cs_, MbtcpClient* tcpC_, tcpIntrfc *parent = 0);
    void displayError(QAbstractSocket::SocketError socketError) override;
    void successConn() override;
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

public slots:
    void connectButt(QString ip_t, QString port_t);
    int periodReqButt(QString ip_t, QString port_t, int t_out);
    void setParamsButt(QString ip_t, QString port_t);
    void getParamsButt(QString ip_t, QString port_t);
    void periodReq(/*QString ip_t, QString port_t*/);
//    void loadDevice_readyRead();
//    void saveDevice_readyRead();


    void load_File_Qml();                   // Load_From_File
    void save_File_Qml(QList<QString> ls);  // Save_To_File
    int load_Device_Qml();                  // send message to load params from device
    int save_Device_Qml();                 // save params to device
//    void load_Default_Qml(QString str);
    void load_Default_Qml(QList<QString> str);
    void commitFromQml(QString str);

    int loadDev_Respond() override;    // receive device's respond after send message to load params from device
    int saveDev_Respond() override;    // receive device's respond after send message tosave params to device
    int loadChart_Respond() override;

private:
    int count;
    configs* cs;
    MbtcpClient* tcpC;
    QTimer probePollTmr;
    chat* cht;
//    QVariant np;
};

#endif // MVCONFIGSCHAT_H
