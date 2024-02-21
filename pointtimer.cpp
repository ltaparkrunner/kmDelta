#include "pointtimer.h"

pointTimer::pointTimer(tcpIntrfc* vmCC, QObject *parent):
    tmr(new QTimer(this))
    ,   str(new QString())
{
    connect(tmr, &QTimer::timeout, vmCC, &tcpIntrfc::timeout_Respond );
}

void pointTimer::setTmr(int i, QString s) {
    tmr->setInterval(i);
    tmr->start();
    *str = s;
}

const QString&  pointTimer::incriment() {
    *str = *str + '.';
    return *str;
}

void pointTimer::stopTmr() {
    tmr->stop();
}
