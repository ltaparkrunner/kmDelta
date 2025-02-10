#ifndef POINTTIMER_H
#define POINTTIMER_H

#include <QObject>
#include <QTimer>
//#include "pTmrIntrfc.h"
//#include "vmConfigsChat.h"
//#include "tcpIntrfc.h"
enum dir_t{
    idle,
    connecting,
    disconnecting
};

class pointTimer : public QObject
{
    Q_OBJECT
public:
    pointTimer(QObject *parent = nullptr);
    void setTmr(int i, QString s, dir_t d);
    const QString& incriment();
    void stopTmr();
    bool isExpired();
    const QTimer* getTmrPtr();
    dir_t get_dir();
signals:
    void expired();
private:
    QTimer* tmr;
    QString* str;
    int attempts;
    dir_t dir;
};

#endif // POINTTIMER_H
