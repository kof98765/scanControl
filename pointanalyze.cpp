#include "pointanalyze.h"
#include "ui_pointanalyze.h"

pointAnalyze::pointAnalyze(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pointAnalyze)
{
    ui->setupUi(this);
    offset=0;
    status=0;
    index=1;
    maxIndex=1;
    isRunning=false;
    QStringList str;

    plot = new Plot(ui->base);
    plot->resize(900,380);

    str<<"point"<<"FrameNum"<<"10"<<"1";
    plot->initPlot(str);
    plot->insertCurve(0,0,"test");
    plot->setYScale(-50,50);
    timer=new QTimer(this);

    connect(timer,SIGNAL(timeout()),this,SLOT(timer_timeout()));

   // timer->start(1);

}

pointAnalyze::~pointAnalyze()
{
    plot->clearCurve();
    timer->stop();
    delete ui;
}

void pointAnalyze::timer_timeout()
{

    static int count=0;



}



