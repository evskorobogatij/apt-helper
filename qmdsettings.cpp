#include "qmdsettings.h"

QmdSettings::QmdSettings(QObject *parent) :
    QObject(parent)
{
    settings = new QSettings("settings.ini",QSettings::IniFormat);
}

void QmdSettings::getConnectSettings(){
    QString host = settings->value("General/host").toString();
    QString base = settings->value("General/base").toString();
    QString user = settings->value("General/user").toString();
    QString pass = settings->value("General/pass").toString();

    qDebug(qPrintable(host));

    emit sendConnectSettings(host,base,user,pass);

}


void QmdSettings::getFindType(){
    int value = settings->value("Find/type",0).toInt();
    emit sendFindType(value);
}

void QmdSettings::getFminCount(){
    int value = settings->value("Find/min_count",3).toInt();
    emit sendFminCount(value);
}
