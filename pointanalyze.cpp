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
    customPlot = new QCustomPlot(ui->base);
    customPlot->resize(300, 300);

       //可变数组存放绘图的坐标的数据，分别存放x和y坐标的数据，101为数据长度


       //添加数据，这里演示y=x^3，为了正负对称，x从-10到+10


       //向绘图区域QCustomPlot添加一条曲线
       customPlot->addGraph();


    //plot = new Plot(ui->base);
    //plot->resize(900,380);

   // str<<"point"<<"FrameNum"<<"10"<<"1";
   // plot->initPlot(str);
   // plot->insertCurve(0,0,"test");
   // plot->setYScale(-50,50);
    timer=new QTimer(this);

    connect(timer,SIGNAL(timeout()),this,SLOT(timer_timeout()));

   // timer->start(1);

}
void pointAnalyze::showData(double *x,double *y,int length)
{
     QVector<double> xd(length), yd(length);

    //添加数据
     for (int i = 0; i<length; i++)
     {
         xd[i] = x[i];
         yd[i] = y[i];
     }
    customPlot->graph(0)->setData(xd, yd);

    //设置坐标轴名称
    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");

    //设置坐标轴显示范围，否则只能看到默认范围
   // customPlot->xAxis->setRange(-11, 11);
   // customPlot->yAxis->setRange(-1100, 1100);
}

pointAnalyze::~pointAnalyze()
{
    //plot->clearCurve();
    timer->stop();
    delete ui;
}

void pointAnalyze::timer_timeout()
{

    static int count=0;



}



