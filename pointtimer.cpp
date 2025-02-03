#include "pointtimer.h"

pointTimer::pointTimer(QObject *parent):
    tmr(new QTimer(this))
    ,   str(new QString())
    , attempts(0)
{
//    connect(tmr, &QTimer::timeout, vmCC, &tcpIntrfc::timeout_Respond );
}

void pointTimer::setTmr(int i, QString s) {
    tmr->setInterval(i);
    tmr->start();
    *str = s;
}

const QString&  pointTimer::incriment() {
    *str = *str + '.';
    if(attempts <= 120) attempts++;
    else
        emit expired();
    return *str;
}

void pointTimer::stopTmr() {
    tmr->stop();
}

bool pointTimer::isExpired(){
    if(attempts > 120) {
        this -> stopTmr();
        return true;
    }
    else return false;
}

const QTimer* pointTimer::getTmrPtr(){
    return tmr;
}
