#ifndef IPADDR_H
#define IPADDR_H

#include <QObject>
#include <QHostAddress>

class IpAddr : public QObject
{
    Q_OBJECT
public:
//    ControlIp();
    explicit IpAddr(QObject *parent = 0);
    void init();
signals:
    //void sendToQml2(QString addr, QString mask, QString port);
    void sendToQml2(QString ip_addr, QString ip_mask, QString ip_port);
public slots:
//    void receiveFromQml();

    void load_File_Qml();
    void save_File_Qml();
    void load_Device_Qml();
    void save_Device_Qml();
    void load_Default_Qml();

    void commitFromQml(QString str);

public:
    QHostAddress get_ip();
    quint16 get_port();
    QString get_ip2();
    QString get_port2();
    QString get_mask2();

private:
    int count;
    QString ip_addr;
    QString ip_mask;
    QString ip_port;  //
};

#endif // IPADDR_H
