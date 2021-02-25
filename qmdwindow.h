#ifndef QMDWINDOW_H
#define QMDWINDOW_H

#include <QWidget>
#include <QtGui/QStandardItemModel>
#include <QtWidgets/QHeaderView>

#include "qmdrlsitem.h"

namespace Ui {
    class QmdWindow;
}

class QmdWindow : public QWidget
{
    Q_OBJECT

public:
    explicit QmdWindow(QWidget *parent = 0);
    ~QmdWindow();

private:
    Ui::QmdWindow *ui;
    int fmin;

signals:
    void findNames(const QString );
    void getNameInfo(const int id);
    void getFminCount();

private slots:
    void prepFindNames(const QString &find);
    void choiseName(const QModelIndex & current, const QModelIndex & previous);
public slots:
    void setFindNames(QStandardItemModel *model);
    void setNameInfo(const RlsItem info);
    void setFminCount(int value);
    void show();

};

#endif // QMDWINDOW_H
