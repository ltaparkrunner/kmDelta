#ifndef MESSBOX_H
#define MESSBOX_H

#include <QObject>

class messBox : public QObject
{
    Q_OBJECT
public:
    explicit messBox(QObject *parent = 0);
signals:
    //void sendToMB(QString &title, QString &text);
public slots:
};

#endif // MESSBOX_H
