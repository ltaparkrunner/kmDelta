#include "ipAddr.h"
#include <QQmlEngine>
#include <QQmlComponent>

IpAddr::IpAddr(QObject *parent) : QObject(parent)
  , ip_addr("192.168.1.170")
  , ip_mask("255.255.0.0")
  , ip_port("502")
{
   // emit sendToQml(ip_addr, ip_mask, port);
}

void IpAddr:: receiveFromQml()
{
    count++;
    //emit sendToQml2(ip_addr, ip_mask, port);
    emit sendToQml2(ip_addr, ip_mask, ip_port);
}
void IpAddr:: commitFromQml(QString str)
{
    QString temp = ip_addr;
    str.append("for");
    ip_addr = str;
    //emit sendToQml2(str, ip_mask, port);
    //emit sendToQml2(ip_addr, ip_mask, port);
    emit sendToQml2(ip_addr, ip_mask, ip_port);
    ip_addr = temp;
    //messageDialog
}
void IpAddr::init()
{
    //emit sendToQml2(ip_addr, ip_mask, port);
    emit sendToQml2(ip_addr, ip_mask, ip_port);
}

QHostAddress IpAddr::get_ip() {
/*
    QQmlEngine engine;
    QQmlComponent component(&engine, "IP_Addr2.qml");
    QObject *obj =
*/
    return QHostAddress(ip_addr);
}

quint16 IpAddr::get_port() {
    // считать из qml

    return ip_port.toShort();
}

QString IpAddr::get_ip2(){
    return ip_addr;
}
QString IpAddr::get_port2() {
    return ip_port;
}
QString IpAddr::get_mask2() {
    return ip_mask;
}

/*
void IpAddr:: receiveFromQml()
{
    count++;
    emit sendToQml(count);
}
*/
