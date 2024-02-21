#ifndef POINTTIMER_H
#define POINTTIMER_H

#include <QObject>
#include <QTimer>
//#include "pTmrIntrfc.h"
//#include "vmConfigsChat.h"
#include "tcpIntrfc.h"

class pointTimer : QObject
{
    Q_OBJECT
public:
    pointTimer(tcpIntrfc* vmCC, QObject *parent = nullptr);
    void setTmr(int i, QString s);
    const QString& incriment();
    void stopTmr();
private:
    QTimer* tmr;
    QString* str;
};

#endif // POINTTIMER_H
