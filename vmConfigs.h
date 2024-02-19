#ifndef MVCONFIGS_H
#define MVCONFIGS_H

#include <QObject>
#include <QString>
#include "tcpIntrfc.h"
#include "configs.h"

class vmConfigs : public tcpIntrfc
{
    Q_OBJECT

public:
    explicit vmConfigs(configs* cs_, MbtcpClient* tcpC_, tcpIntrfc *parent = 0);
    void displayError(QAbstractSocket::SocketError socketError) override;
    void successConn() override;
    configs getCs() const;
//    ~vmConfigs();
signals:
    void sendToMB(const QString &title, const QString &text);
    void sendToQml(qint16 count);
    void sendToChat(QVariantList abs);
    void sendToDialog(const QString &title);
    void sendCurrIp(QList<QString> ls);
    void sendCurrIp_2(const QString &ls);
    void sendErrFileOpen(const QString &title);
    void saveFileSucc(const QString &title);

public slots:
    void connectButt(QString ip_t, QString port_t);
    void periodReqButt(QString ip_t, QString port_t, int t_out);
    void setParamsButt(QString ip_t, QString port_t);
    void getParamsButt(QString ip_t, QString port_t);
    void periodReq(/*QString ip_t, QString port_t*/);
//    void loadDevice_readyRead();
//    void saveDevice_readyRead();


    void load_File_Qml();
    void save_File_Qml(QList<QString> ls);
    void load_Device_Qml();
    void save_Device_Qml();
//    void load_Default_Qml(QString str);
    void load_Default_Qml(QList<QString> str);
    void commitFromQml(QString str);

    void loadDev_Respond() override;
    void saveDev_Respond() override;
    void loadChart_Respond() override;

private:
    int count;
    configs* cs;
    MbtcpClient* tcpC;
//    QVariant np;
};

#endif // MVCONFIGS_H
