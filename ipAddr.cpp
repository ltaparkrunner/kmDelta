#include "ipAddr.h"

IpAddr::IpAddr(QObject *parent) : QObject(parent)
  , ip_addr("192.168.0.1")
  , ip_mask("255.255.255.0")
  , port("502")
{
   // emit sendToQml(ip_addr, ip_mask, port);
}

void IpAddr:: receiveFromQml()
{
    count++;
    emit sendToQml2(ip_addr, ip_mask, port);
}
void IpAddr:: commitFromQml(QString str)
{
    str.append("for");
    emit sendToQml2(str, ip_mask, port);
    //messageDialog
}
void IpAddr::init()
{
    emit sendToQml2(ip_addr, ip_mask, port);
}
/*
void IpAddr:: receiveFromQml()
{
    count++;
    emit sendToQml(count);
}
*/
