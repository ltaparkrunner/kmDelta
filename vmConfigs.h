#ifndef MVCONFIGS_H
#define MVCONFIGS_H

#include <QObject>
#include <QString>
#include "tcpman.h"
#include "configs.h"

//struct net_p{
//    QString ip_t;
//    QString port_t;
//};

class vmConfigs : public tcpMan
{
    Q_OBJECT
private:
//    Q_PROPERTY(QVariantList np_p READ getParamsButt /*WRITE setParamsButt*/ NOTIFY  ParamsChanged)
    Q_PROPERTY(QVariant np_p READ getParamsButt WRITE setParamsButt NOTIFY  ParamsChanged)
    Q_PROPERTY(QString ip_n READ ip_n WRITE setIp NOTIFY  ipChanged)
public:
    explicit vmConfigs(configs cs_, tcpMan *parent = 0);
    void displayError(QAbstractSocket::SocketError socketError) override;
    void successConn() override;
    configs getCs() const;
//    ~vmConfigs();
signals:
    void sendToMB(const QString &title, const QString &text);
    void sendToQml(qint16 count);
    void sendToChat(QVariantList abs);
    void sendToDialog(const QString &title);
    void ParamsChanged(QVariant n);
    void ipChanged(QString ip_n);

public slots:
    void connectButt(QString ip_t, QString port_t);
    void periodReqButt(QString ip_t, QString port_t, int t_out);
//    void setParamsButt(QString ip_t, QString port_t);
    void setParamsButt(QVariant n);
//    void getParamsButt(QString ip_t, QString port_t);
    QVariant getParamsButt();
    QString ip_n() const;
    void setIp(QString ip_n);
    void periodReq(/*QString ip_t, QString port_t*/);
    void dbg_message(QVariant n);
    void dbg_message2(QString n);

private:
    configs cs;
    QVariant np;
};

#endif // MVCONFIGS_H
