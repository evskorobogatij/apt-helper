#include "qmdcontroler.h"

QmdControler::QmdControler(QObject *parent) :
    QObject(parent)
{
}

int QmdControler::init(){

    base = new QmdBase();
    settings = new QmdSettings();
    wmain = new QmdWindow();

    QObject::connect(wmain,SIGNAL(findNames(QString)),base,SLOT(getNameList(QString)));
    QObject::connect(base,SIGNAL(sendNameList(QStandardItemModel*)),wmain,SLOT(setFindNames(QStandardItemModel*)));

    QObject::connect(wmain,SIGNAL(getNameInfo(int)),base,SLOT(getNameInfo(int)));
    QObject::connect(base,SIGNAL(sendNameInfo(RlsItem)),wmain,SLOT(setNameInfo(RlsItem)));

    QObject::connect(base,SIGNAL(getConnectParam()),settings,SLOT(getConnectSettings()));
    QObject::connect(settings,SIGNAL(sendConnectSettings(QString,QString,QString,QString)),
                     base,SLOT(setConnectParam(QString,QString,QString,QString)));

    QObject::connect(wmain,SIGNAL(getFminCount()),settings,SLOT(getFminCount()));
    QObject::connect(settings,SIGNAL(sendFminCount(int)), wmain, SLOT(setFminCount(int)));

    QObject::connect(base,SIGNAL(getFindType()),settings,SLOT(getFindType()));
    QObject::connect(settings,SIGNAL(sendFindType(int)),base,SLOT(setFindType(int)));

    if (base->connect()==-1) return -1;
    wmain->show();

    return 0;
}
