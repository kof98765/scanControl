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

    str<<"point"<<"FrameNum"<<"1000"<<"10";
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

void pointAnalyze::on_loadButton_clicked()
{
    filePath=QFileDialog::getOpenFileName(this,QStringLiteral("选择点云数据"),".","",0,0);
    qDebug()<<filePath;
    index=1;
    readPointCloudDate(filePath);


   // readFrame();
}
void pointAnalyze::readPointCloudDate(QString str)
{

    status=0;
    QFile f(str);
    if(str.isEmpty())
        return;
    int ind=0;
    if(!f.open(QIODevice::ReadOnly))
    {

    }
   // if(!buf->isEmpty())
     //   delete buf;
    buf=new QByteArray(f.readAll());
    int start=0,end;

    for(int i=0;i<FRAME_LENGTH;i++)
    {
       qDebug()<<buf->mid(0,50);
       end=buf->indexOf(' ',start);
       data.append(buf->mid(start,end-start).toDouble());
       qDebug()<<data.at(i);

       start=end+1;
    }


    offset=end+1;
    first_offset=offset;
    f.close();
    status=1;



}
void pointAnalyze::on_nextFrame_clicked()
{
    if(!mux.tryLock())
        return;

    if(index<maxIndex)
    {


        ui->numFrame->setValue(ui->numFrame->value()+1);
        readFrame();
    }
    mux.unlock();

}
void pointAnalyze::readFrame()
{

   double x[FRAME_LENGTH];
   double y[FRAME_LENGTH];
    for(int i=0;i<FRAME_LENGTH;i++)
    {
        x[i]=i;
        y[i]=data.at((index-1)*FRAME_LENGTH+i);
    }

    //d_plot->insertCurve(yData,FRAME_LENGTH,"point could");
     plot->upDate2(x,y,FRAME_LENGTH);
    qDebug()<<index;
}


void pointAnalyze::on_preFrame_clicked()
{
    if(index>1)
        ui->numFrame->setValue(ui->numFrame->value()-1);
    else
        on_reset_clicked();
    readFrame();


}

void pointAnalyze::on_reset_clicked()
{
    plot->setYScale(-50,50);
    ui->numFrame->setValue(1);
    index=1;
    maxIndex=1;
    status=0;
    offset=0;
}

void pointAnalyze::on_numFrame_valueChanged(int arg1)
{
   // if(abs(arg1-index)>2)
    //    index=arg1;
    index=ui->numFrame->value();
    //readFrame();
}

void pointAnalyze::on_pushButton_clicked()
{
    if(isRunning)
    {
        isRunning=false;
        //timer->stop();
        ui->pushButton->setText("start");
        status=1;
    }
    else
    {
        isRunning=true;

        ui->pushButton->setText("stop");
        status=2;
    }
}
void pointAnalyze::timer_timeout()
{

    static int count=0;
    switch(status)
    {
    mux.lock();
        case 1:
        case 2:
            if(offset < (buf->size())-first_offset)
            {
                    int start=offset,end;

                    end=buf->indexOf(' ',start);
                    data.append(buf->mid(start,end-start).toDouble());

                    start=end+1;

                    offset=end+1;

                    count++;
                    if(count>FRAME_LENGTH)
                    {

                        count=0;
                        maxIndex++;

                    }
            }


            if(isRunning)
            {
                if(index<maxIndex)
                {

                    if(index>1000)
                    {
                        ui->numFrame->setValue(0);
                    }
                    else
                        ui->numFrame->setValue(ui->numFrame->value()+1);
                    readFrame();
                }
            }
            break;
             mux.unlock();
        }


}



