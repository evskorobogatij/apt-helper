#include "qmdbase.h"

QmdBase::QmdBase(QObject *parent) :
    QObject(parent)
{
}

void QmdBase::setConnectParam(const QString ahost, const QString abase, const QString auser, const QString apass){
    hosname = ahost;
    base = abase;
    user = auser;
    pass = apass;
}

int QmdBase::connect(){

    emit getConnectParam();

    qDebug("prepare connecting...");
    db = QSqlDatabase::addDatabase("QPSQL","med_rls");
    db.setHostName(hosname);
    db.setDatabaseName(base);
    db.setUserName(user);
    db.setPassword(pass);

    if (!db.open()) {
        QMessageBox::warning(0,"",db.lastError().text(),QMessageBox::Close);
        return -1;
    }

    qDebug("connected");
    query = new QSqlQuery(db);

    findType = 0 ;
    emit getFindType();

    return 0;
}

void QmdBase::getNameInfo(const int id){
    db.transaction();
    QString s = "select \"FIRM_MANUFACTOR\" , \"COUNTRY_MANUFACTOR\", "
            "\"FIRM_REGISTRATOR\", \"COUNTRY_REGISTRATOR\", \"REGNUM\", \"REGDATE\", \"REGCERTID\", "
            " \"ATC\", \"PHARMGROUP\", \"OKDP\", "
            " \"NDV\", \"JNVLS\"  "
            "from rls.info where id=:id ";
    query->prepare(s);
    query->bindValue(":id",id);

    if (!query->exec()) {
        db.rollback();
        QMessageBox::warning(0,"",query->lastError().text(),QMessageBox::Close);
        return;
    }

    qDebug(qPrintable("start find: "+QString::number(id)));

    RlsItem info;
    if (query->next()) {
        info.FIRM_MANUFACTOR = query->value(0).toString();
        info.COUNTRY_MANUFACTOR = query->value(1).toString();
        info.FIRM_REGISTRATOR = query->value(2).toString();
        info.COUNTRY_REGISTRATOR = query->value(3).toString();
        info.REGNUM = query->value(4).toString();
        info.REGDATE = query->value(5).toDate().toString("d MMMM yyyy");
        info.REGCERTID = query->value(6).toString();
        int atc = query->value(7).toInt();
        QSqlQuery *vquery = new QSqlQuery(db);
        vquery->prepare("select name from \"Atc\" where id=:id");
        vquery->bindValue(":id",atc);
        if (!vquery->exec()) {
            db.rollback();
            return;
        }
        if (vquery->next()) {
           info.ATC = vquery->value(0).toString();
        }
        //delete vquery;

        //info.ATC = query->value(7).toString();


        //QList<int> farmgroup_codes;

        //qDebug(qPrintable("OKDP "+query->value(9).toString()));


//        vquery->prepare("select name from \"farmgroup\" where id in (:id)");
//        vquery->bindValue(":id",query->value(8).toString());
        QList<quint64> fg_code;
        QStringList fgs = query->value(8).toString().split(",");
        foreach (QString s, fgs) {
            fg_code<<s.toULongLong();
        }
        QStringList fg_l;
        foreach (quint64 v, fg_code) {
            fg_l<<QString::number(v);
        }
        QString q_fg = "select name from \"farmgroup\" where id in (";
        q_fg.append(fg_l.join(", "));
        q_fg.append(")");
        if (!vquery->exec(q_fg)) {
            db.rollback();
            QMessageBox::warning(0,"",vquery->lastError().text(),QMessageBox::Close);
            return;
        }
        QStringList farmgroup;
        while (vquery->next()) {
            farmgroup<<vquery->value(0).toString();
        }
        info.PHARMGROUP = farmgroup.join("\n");
                //query->value(8).toString();


        QList<quint64> okdp_code;
        QStringList okdps = query->value(9).toString().split(",");
        foreach (QString s, okdps) {
            okdp_code<<s.toULongLong();
        }
        QStringList okdp_l;
        foreach (quint64 v, okdp_code) {
            okdp_l<<QString::number(v);
        }
        QString q_okdp = "select name from okdp where id in (";
        q_okdp.append(okdp_l.join(", "));
        q_okdp.append(")");
//        vquery->prepare("select name from okdp where id in (:id)");
//        vquery->bindValue(":id",query->value(9).toString());
        if (!vquery->exec(q_okdp)) {
            db.rollback();
            QMessageBox::warning(0,"",vquery->lastError().text(),QMessageBox::Close);
            return;
        }
        QStringList okdp;
        while (vquery->next()) {
            QStringList str = vquery->value(0).toString().split(" ");
            if (str.count()>1) {
                QString s=str.at(0);
//                s.prepend("<b>");
//                s.append("</b>");
                str.replace(0,s);
            }
            okdp<<str.join(" ");
        }

        info.OKDP = okdp.join("\n\r");
                //query->value(9).toString().replace(",","\n");
        qDebug(qPrintable("OKDP "+query->value(9).toString()));

        info.NDV = query->value(10).toString();


        info.JNVLS = query->value(11).toInt();

        vquery->prepare("select prices.price from rls.prices, rls.info where (prices.id=info.rcode) and  (info.id=:id)");
        vquery->bindValue(":id",id);

        if (!vquery->exec()) {
            db.rollback();
            QMessageBox::warning(0,"",vquery->lastError().text(),QMessageBox::Close);
            return;
        }
        info.regPrice = 0;
        if (vquery->next()) {
            info.regPrice = vquery->value(0).toDouble();
        }

    }



    db.commit();

    emit sendNameInfo(info);
}

void QmdBase::setFindType(int value){
    findType = value;
}

void QmdBase::getNameList(const QString &find){
    db.transaction();
    switch (findType){
    case 0 : {
        QString s = "SELECT id,  \"NAME\", \"STATUS\", \"JNVLS\" FROM rls.info WHERE upper(\"NAME\") LIKE :NAME||\'\%\' ";
        query->prepare(s);
        qDebug(qPrintable(query->lastError().driverText()));
        qDebug(qPrintable(query->lastError().databaseText()))   ;
        query->bindValue(":NAME",find.toUpper());
        break;
    }
    case 1 : {
       QString s = "SELECT distinct id,  \"NAME\", \"STATUS\",  \"JNVLS\", similarity(upper(\"TRADENAME\"),:FN) as sn FROM rls.info WHERE upper(\"TRADENAME\") % :NAME order by sn DESC  ";
       query->prepare(s);
       query->bindValue(":FN",find.toUpper());
       query->bindValue(":NAME",find.toUpper());
       break;
    }
    }

//    QString s = "SELECT id,  \"NAME\", \"STATUS\" FROM rls.info WHERE upper(\"NAME\") LIKE :NAME||\'\%\' ";
//  //   QString s = "SELECT distinct id,  \"NAME\", \"STATUS\", similarity(upper(\"TRADENAME\"),:FN) as sn FROM rls.info WHERE upper(\"TRADENAME\") % :NAME order by sn DESC  ";
//    query->prepare(s);
//  //  query->bindValue(":FN",find.toUpper());
//    query->bindValue(":NAME",find.toUpper());

    if (!query->exec()) {
        db.rollback();
        QMessageBox::warning(0,"",query->lastError().text(),QMessageBox::Close);
        return;
    }

    QStandardItemModel *model = new QStandardItemModel(0,1);
    while (query->next()) {
        QList<QStandardItem*> list;

        QStandardItem *id = new QStandardItem();
        id->setData(query->value(0).toInt(),Qt::DisplayRole);

        QStandardItem *name = new QStandardItem();
        name->setData(query->value(1).toString(),Qt::DisplayRole);

        int status = query->value(2).toInt();
        if (status!=1) {
            name->setData(QColor(0xDE,0x42,0x30,0x91),Qt::BackgroundColorRole);
        }

        int jnvls = query->value(3).toInt();
        if (jnvls==2) {
            name->setData(QIcon(":/coins.png"),Qt::DecorationRole);
        }
//        QStandardItem *sm = new QStandardItem();
//        sm->setData(query->value(3).toDouble(),Qt::DisplayRole);

        list<<id<<name/*<<sm*/;
        model->appendRow(list);

//        qApp->processEvents();
    }


    db.commit();

    emit sendNameList(model);

}
