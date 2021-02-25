#ifndef QMDSETTINGS_H
#define QMDSETTINGS_H

#include <QObject>
#include <QtCore/QSettings>

class QmdSettings : public QObject
{
    Q_OBJECT
public:
    explicit QmdSettings(QObject *parent = 0);

signals:
    void sendConnectSettings(const QString ahost, const QString abase, const QString auser, const QString apass);
    void sendFminCount(int );
    void sendFindType(int );

public slots:
    void getConnectSettings();
    void getFindType();
    void getFminCount();
private:
    QSettings *settings;

};

#endif // QMDSETTINGS_H
