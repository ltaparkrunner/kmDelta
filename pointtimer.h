#ifndef POINTTIMER_H
#define POINTTIMER_H

#include <QObject>
#include <QTimer>
//#include "pTmrIntrfc.h"
//#include "vmConfigsChat.h"
//#include "tcpIntrfc.h"

class pointTimer : public QObject
{
    Q_OBJECT
public:
    pointTimer(QObject *parent = nullptr);
    void setTmr(int i, QString s);
    const QString& incriment();
    void stopTmr();
    bool isExpired();
    const QTimer* getTmrPtr();
signals:
    void expired();
private:
    QTimer* tmr;
    QString* str;
    int attempts;
};

#endif // POINTTIMER_H
