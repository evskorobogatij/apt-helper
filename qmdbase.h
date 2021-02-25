#ifndef QMDBASE_H
#define QMDBASE_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtWidgets/QMessageBox>
#include <QtGui/QStandardItemModel>
#include <QtCore/QDate>
#include <QtCore/QCoreApplication>

#include "qmdrlsitem.h"

class QmdBase : public QObject
{
    Q_OBJECT
public:
    explicit QmdBase(QObject *parent = 0);
    
signals:
    void sendNameList(QStandardItemModel *model);
    void sendNameInfo(RlsItem info);
    void getConnectParam();
    void getFindType();
public slots:
    int connect();
    void getNameList(const QString &find);
    void getNameInfo(const int id);
    void setConnectParam(const QString ahost, const QString abase, const QString auser, const QString apass);
    void setFindType(int value);
private:
    QSqlDatabase db;
    QSqlQuery *query;

    QString hosname;
    QString base;
    QString user;
    QString pass;

    int findType;
    
};

#endif // QMDBASE_H
