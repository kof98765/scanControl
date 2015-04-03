#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include <QtDebug>
#include <QFile>
#include <QTextStream>

void customMessageHandler(QtMsgType type, const char *msg)
{
    QString txt;
    switch (type) {
    case QtDebugMsg:
        txt = QString("Debug: %1").arg(msg);
        break;

    case QtWarningMsg:
        txt = QString("Warning: %1").arg(msg);
    break;
    case QtCriticalMsg:
        txt = QString("Critical: %1").arg(msg);
    break;
    case QtFatalMsg:
        txt = QString("Fatal: %1").arg(msg);
        abort();
    }

    QFile outFile("debuglog.txt");
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    ts << txt << endl;
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QLibrary mylib("halconclass.dll");
    QCoreApplication::setOrganizationName("EDAC");
    QCoreApplication::setApplicationName("ipad");

    MainWindow w;

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf8"));

    //qInstallMsgHandler(customMessageHandler);
    //w.setWindowFlags(Qt::FramelessWindowHint);

  //  QSplashScreen *screen=new QSplashScreen;
   // screen->setPixmap(QPixmap(":/new/prefix1/ico.png"));
   // screen->show();
    //QTimer time;
   // time.singleShot(2000,&w,SLOT(showMaximized()));
    //time.singleShot(3000,screen,SLOT(hide()));
        w.resize(1280,748);
        w.show();

    QIcon ico(":/new/prefix1/ico/ico.png");
    a.setWindowIcon(ico);

    return a.exec();
}
