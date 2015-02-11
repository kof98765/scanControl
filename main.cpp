#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QLibrary mylib("halconclass.dll");
    QCoreApplication::setOrganizationName("EDAC");
    QCoreApplication::setApplicationName("ipad");

    MainWindow w;

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf8"));


    //w.setWindowFlags(Qt::FramelessWindowHint);

  //  QSplashScreen *screen=new QSplashScreen;
   // screen->setPixmap(QPixmap(":/new/prefix1/ico.png"));
   // screen->show();
    //QTimer time;
   // time.singleShot(2000,&w,SLOT(showMaximized()));
    //time.singleShot(3000,screen,SLOT(hide()));
        w.resize(1024,748);
        w.show();

    QIcon ico(":/new/prefix1/ico.png");
    a.setWindowIcon(ico);

    return a.exec();
}
