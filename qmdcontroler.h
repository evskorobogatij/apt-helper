#ifndef QMDCONTROLER_H
#define QMDCONTROLER_H

#include <QObject>

#include "qmdwindow.h"
#include "qmdbase.h"
#include "qmdrlsitem.h"
#include "qmdsettings.h"

class QmdControler : public QObject
{
    Q_OBJECT
public:
    explicit QmdControler(QObject *parent = 0);

signals:

public slots:
    int init();
private:
    QmdWindow *wmain;
    QmdBase *base;
    QmdSettings *settings;

};

#endif // QMDCONTROLER_H
