#include "pointtimer.h"

pointTimer::pointTimer(QObject *parent):
    tmr(new QTimer(this))
    ,   str(new QString())
    , attempts(0)
    , dir(idle)
{

}

void pointTimer::setTmr(int i, QString s, dir_t d) {
    dir = d;
    tmr->setInterval(i);
    tmr->start();
    *str = s;
}

const QString&  pointTimer::incriment() {
    *str = *str + '.';
    if(attempts <= 122) attempts++;
    else
        emit expired();
    if(attempts > 120) emit expired();
    return *str;
}

void pointTimer::stopTmr() {
    tmr->stop();
}

bool pointTimer::isExpired(){
    if(attempts > 124) {
        this -> stopTmr();
        return true;
    }
    else return false;
}

const QTimer* pointTimer::getTmrPtr(){
    return tmr;
}

dir_t pointTimer::get_dir(){
    return dir;
}
