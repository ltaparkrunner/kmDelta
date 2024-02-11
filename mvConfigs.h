#ifndef MVCONFIGS_H
#define MVCONFIGS_H

#include <QObject>
#include <QString>
#include "tcpman.h"
#include "configs.h"

class mvConfigs : public tcpMan
{
    Q_OBJECT
public:
    explicit mvConfigs(configs cs_, tcpMan *parent = 0);
    void displayError(QAbstractSocket::SocketError socketError) override;
    void successConn() override;
//    ~mvConfigs();
signals:
    void sendToMB(const QString &title, const QString &text);
    void sendToQml(qint16 count);
    void sendToChat(QVariantList abs);
    void sendToDialog(const QString &title);

public slots:
    void connectButt(QString ip_t, QString port_t);
    void periodReqButt(QString ip_t, QString port_t, int t_out);
    void setParamsButt(QString ip_t, QString port_t);
    void getParamsButt(QString ip_t, QString port_t);
    void periodReq(/*QString ip_t, QString port_t*/);

private:
    configs cs;
};

#endif // MVCONFIGS_H
