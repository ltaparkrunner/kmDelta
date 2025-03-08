#ifndef PTMRINTRFC_H
#define PTMRINTRFC_H

#include <QObject>

class pTmrIntrfc : public QObject
{
    Q_OBJECT
public:
//    pTmrIntrfc(QObject *parent) : QObject(parent){}
public slots:
    virtual int timeout_Respond() = 0;
};

#endif // PTMRINTRFC_H
