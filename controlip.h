#ifndef CONTROLIP_H
#define CONTROLIP_H

#include <QObject>

class ControlIp : public QObject
{
    Q_OBJECT
public:
//    ControlIp();
    explicit ControlIp(QObject *parent = 0);

signals:
    void sendToQml(int count);
public slots:
    void receiveFromQml();
private:
    int count;
};

#endif // CONTROLIP_H
