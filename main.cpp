#include <QApplication>
#include <QtCore/QTextCodec>

#include "qmdcontroler.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec *codec=QTextCodec::codecForName("UTF-8");
//    QTextCodec::setCodecForTr(codec);
//    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForLocale(codec);


    QmdControler *controler = new QmdControler();
    int res=controler->init();
    if (res==-1) return -1;

    return a.exec();
}
