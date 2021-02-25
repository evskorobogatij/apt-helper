#include "qmdwindow.h"
#include "ui_qmdwindow.h"

QmdWindow::QmdWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QmdWindow)
{
    ui->setupUi(this);


    QObject::connect(ui->eFind,SIGNAL(textChanged(QString)),this,SLOT(prepFindNames(QString)));

    this->resize(800,600);
    ui->box->setCurrentWidget(ui->noresultBox);

    fmin = 3;

}

QmdWindow::~QmdWindow()
{
    delete ui;
}

void QmdWindow::setFminCount(int value){
    fmin = value;
}

void QmdWindow::setFindNames(QStandardItemModel *model){

    QObject::disconnect(ui->view->selectionModel(),SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
                     this,SLOT(choiseName(QModelIndex,QModelIndex)));

    if (model->rowCount()>0) {
        ui->view->setModel(model);
        ui->view->setColumnHidden(0,true);
        ui->view->setWordWrap(true);
        ui->view->resizeRowsToContents();
        ui->view->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
//                setResizeMode(1,QHeaderView::Stretch);
        QObject::connect(ui->view->selectionModel(),SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
                         this,SLOT(choiseName(QModelIndex,QModelIndex)));

        ui->view->selectRow(0);

        ui->box->setCurrentWidget(ui->findBox);
    } else {
        ui->box->setCurrentWidget(ui->noresultBox);
    }


}

void QmdWindow::prepFindNames(const QString &find){
    if (find.simplified().count()>=fmin) {
        emit findNames(find);
    }
}

void QmdWindow::show(){
    emit getFminCount();
    QWidget::show();
}

void QmdWindow::choiseName(const QModelIndex &current, const QModelIndex &previous){
    ui->prices->setVisible(false);
    int row = current.row();

    int id = ui->view->model()->data(
                ui->view->model()->index(row,0,QModelIndex()),Qt::DisplayRole).toInt();

    qDebug(qPrintable(QString::number(id)));
    emit getNameInfo(id);
}

void QmdWindow::setNameInfo(const RlsItem info){
    ui->cNDV->setText(info.NDV);
    ui->cManufactor->setText(info.FIRM_MANUFACTOR+" ("+info.COUNTRY_MANUFACTOR+")");
    ui->cRegistrator->setText(info.FIRM_REGISTRATOR+" ("+info.COUNTRY_REGISTRATOR+")");
    ui->cRegNum->setText(info.REGNUM);
    ui->cRegDate->setText(info.REGDATE);
    ui->cRegSert->setText(info.REGCERTID);
    ui->cAtc->setText(info.ATC);
    ui->cPharmGroup->setText(info.PHARMGROUP);
    ui->cOKDP->setText(info.OKDP);

    //if () {
        ui->prices->setVisible(info.JNVLS==2);
   // }

    ui->regPrice->setText(QString::number(info.regPrice)+" руб.");
    double opt_p;
    if (info.regPrice<=50) {
        opt_p = 0.15;
    } else {
        if (info.regPrice<=500) {
            opt_p = 0.10;
        } else {
            opt_p = 0.08;
        }
    }

    double optPrice = info.regPrice*opt_p+info.regPrice;
    ui->optPrice->setText(QString::number(optPrice)+" руб.");

    double rozn_p;
    if (info.regPrice<=50) {
        rozn_p = 0.3;
    } else {
        if (info.regPrice<=500) {
            rozn_p = 0.2;
        } else {
            rozn_p = 0.16;
        }
    }

    double roznPrice = info.regPrice*rozn_p+optPrice;
    ui->roznPrice->setText(QString::number(roznPrice)+" руб.");
    ui->roznPriceNDS->setText(QString::number(roznPrice*1.1)+" руб.");

}


