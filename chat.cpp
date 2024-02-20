#include "chat.h"

chat::chat()
{
//    QObject::connect(&probePollTmr, &QTimer::timeout, this, &ControlIp::periodReq);
}

int chat::get_tcp_chatdata(MbtcpClient* tcpC){
    return 0;
}

QList<qint32>* chat::get_tcp_chatdata_resp(MbtcpClient* tcpC) {
    return new QList<qint32>();
}

//int startTimer() {

//}

//int timerEvent() {

//}
