#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "setdialog.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

   ui->setupUi(this);
   readSettings();

//初始化
   isRunning=false;
   isDrag=false;
   isDrawing=false;
   isAuto=false;
   leftRightPress=false;
   leftPress=false;
   rightPress=false;
   index=0;
   pass=0;
   preIndex=-1;

   profile=new profileGet();


    plot = new Plot(ui->base->widget(2));
    QStringList str;
    str<<"value"<<"pointNum"<<"1280"<<"100";
    plot->initPlot(str);
    plot->insertCurve(0,0,"test");
    plot->setYScale(-100,100);
    plot->setXScale(-40,40);
    plot->resize(ui->base->widget(2)->size());

    timer=new QTimer();

    sum=new summarizing;
    sum->set_table(ui->tableWidget);
    mygroup = new QButtonGroup;
    mygroup->addButton(ui->imgUp,0);
    mygroup->addButton(ui->imgDown,1);
    mygroup->addButton(ui->imgLeft,2);
    mygroup->addButton(ui->imgRight,3);
    mygroup->addButton(ui->imgBig,4);
    mygroup->addButton(ui->imgSmall,5);
    mygroup->addButton(ui->imgRotate,6);

    ui->progressBar->setMaximum(100);

//加载检测查块
    hal=new halconClass;
    ref=new reflectControl;
   // glWidget = new GLWidget;
   // QGridLayout *layout=new QGridLayout;
   // layout->addWidget(glWidget);
    //ui->base->setLayout(layout);
  //  writeData = new writeExcel;

    //网络设置对话框
    dialNet = new DialogNetParam;
    dialNet->setModal(true);

    point=new pointAnalyze;

   //激活鼠标跟踪功能
    setMouseTracking(true);
    ui->centralWidget->setMouseTracking(true);
    ui->base->setMouseTracking(true);
    ui->base->installEventFilter(this);
    ui->view_box->installEventFilter(this);
    //glWidget->setMouseTracking(true);
    init_connect();

}

bool MainWindow::eventFilter(QObject *target, QEvent *event)
{
    static QPoint start,end;

    if(target==ui->base)
    {


        if(event->type()==QEvent::MouseButtonPress)
        {

            QMouseEvent *mouse=static_cast<QMouseEvent *>(event);

            if(mouse->button()==Qt::LeftButton)
                leftPress=true;
            if(mouse->button()==Qt::RightButton)
                rightPress=true;
            start=mouse->pos();

            isDrag=true;

        }

        if(event->type()==QEvent::MouseMove)
        {
            QMouseEvent *mouse=static_cast<QMouseEvent *>(event);
            end=mouse->pos();


            //start=mouse->pos();
            if(isDrag)
            {

                int x,y;
                x=end.x()-start.x();
                y=end.y()-start.y();
               if(isDrawing)
               {


               }
               else
               {
                   if((abs(x)>10)|(abs(y)>10))
                        hal->moveImg(start.x()-end.x(),start.y()-end.y());

                   if(leftPress&rightPress)
                   {
                       hal->threedControl(end.x(),end.y(),start.x(),start.y(),"move");

                   }
                   else if(leftPress)
                   {
                       hal->threedControl(end.x(),end.y(),start.x(),start.y(),"rotate");

                   }
                   else if(rightPress)
                   {
                       hal->threedControl(end.x(),end.y(),start.x(),start.y(),"scale");

                   }

               }
            }
        }
        if(event->type()==QEvent::MouseButtonRelease)
        {
            QMouseEvent *mouse=static_cast<QMouseEvent *>(event);
            end=mouse->pos();
            isDrag=false;
            if(mouse->button()==Qt::LeftButton)
                leftPress=false;
            else if(mouse->button()==Qt::RightButton)
                rightPress=false;
            if(isDrawing)
            {

            }
            else
                hal->set_pos(start.x()-end.x(),start.y()-end.y());

        }

        if(event->type()==QEvent::ContextMenu)
        {
            if(!isDrawing)
            {
                /*
                QContextMenuEvent *mouse=static_cast<QContextMenuEvent *>(event);
                QMenu menu(this);
                menu.addAction(ui->action_big);
                menu.addAction(ui->action_small);
                menu.exec(mouse->globalPos());
                */
            }
        }

        if(event->type()==QEvent::Wheel)
            return QWidget::eventFilter(target,event);
        return true;

    }
    else
       return  QWidget::eventFilter(target,event);

}

void MainWindow::resizeEvent(QResizeEvent *event)
{


    ui->base->setStyleSheet(QLatin1String(
    "border:2px;\n"
    "border-radius:5px"));
    event->accept();
    //QString("QGroupBox:title { color: rgb(255,0,0); }");
}
/*
    函数名:init_connect()
    参数:无
    返回值:无
    作用:
    初始化信号槽

*/
void MainWindow::init_connect()
{

    connect(ui->action_about,SIGNAL(triggered()),this,SLOT(about()));
    connect(ui->action_Net_Param,SIGNAL(triggered()),this,SLOT(Net_Param()));

    connect(ui->action_Quit,SIGNAL(triggered()),this,SLOT(on_action_Quit_triggered()));

    connect(ui->action_big,SIGNAL(triggered()),hal,SLOT(zoomOut()));
    connect(ui->action_small,SIGNAL(triggered()),hal,SLOT(zoomIn()));

    //点击开始按钮开始检测
    connect(ui->action_start,SIGNAL(triggered()),this,SLOT(startButton_clicked()));
    //connect(point,SIGNAL(initDevice()),profile,SLOT(initDevice()));
    connect(hal,SIGNAL(dispImg()),this,SLOT(dispImg()));
    connect(ui->settings,SIGNAL(clicked()),ui->action_Net_Param,SLOT(trigger()));
    connect(ui->settings,SIGNAL(clicked()),this,SLOT(on_textChanged()));
    connect(mygroup,SIGNAL(buttonClicked(int)),this,SLOT(controlImg(int)));
    connect(ref,SIGNAL(recvData(char*)),dialNet,SLOT(recvData(char*)));
    connect(dialNet,SIGNAL(netTest(QString)),this,SLOT(netTest(QString)));
    connect(ui->action_pointAnalyze,SIGNAL(triggered()),point,SLOT(show()));

    connect(MsgHandlerWapper::instance(),SIGNAL(message(QtMsgType,QString)),this,
                    SLOT(outputMessage(QtMsgType,QString)));

    connect(hal,SIGNAL(sendHeightSub(double,double,double,double,double,double))
            ,this,SLOT(recvHeightSub(double,double,double,double,double,double)));
    connect(profile,SIGNAL(dispZ(QString)),hal,SLOT(read_img(QString)));
    connect(profile,SIGNAL(putImagebyPointer1(double*,int,int)),hal,SLOT(getImagebyPointer1(double*,int,int)));
    connect(profile,SIGNAL(putImagebyPointer3(double*,double*,double*,int,int)),hal,SLOT(getImagebyPointer3(double*,double*,double*,int,int)));
    //connect(profile,SIGNAL(setData(double*,int)),glWidget,SLOT(setData(double*,int)));
    connect(profile,SIGNAL(Error(QString)),this,SLOT(Error(QString)));
    connect(profile,SIGNAL(dispSingleFrame(double*,double*,int)),plot,SLOT(upDate(double*,double*,int)));
    connect(profile,SIGNAL(dispFrame(unsigned char*,int)),this,SLOT(dispFrame(unsigned char*,int)));
}

void MainWindow::Error(QString str)
{

    QMessageBox::warning(this,
                         QStringLiteral("错误"),
                         str,
                         QMessageBox::Yes );
}
void MainWindow::modeSelect(int i)
{
    if(i==0)
    {
        ui->startButton->setText(QStringLiteral("开始处理"));
        ui->startButton->setCheckable(false);
        isRunning=false;
        isAuto=false;
    }
    else
    {
        ui->startButton->setCheckable(true);
        isAuto=true;
    }
}

void MainWindow::selectImg(int index)
{
    this->index=index;
    fileName=fileList.at(index);
    hal->read_img(fileList.at(index));

    ui->progressBar->setValue(20);
    ui->progressBar->setFormat(QStringLiteral("%p%加载文件中.."));
    ui->progressBar->repaint();
    if(!isAuto)
    {
        ui->startButton->setEnabled(false);
        ui->action_start->setEnabled(false);
    }
}
void MainWindow::dispFrame(unsigned char *buf,int size)
{
    palette.setBrush(ui->base->widget(1)->backgroundRole(),QBrush(QImage::fromData(buf,size)));
    ui->base->widget(1)->setPalette(palette);
}
void MainWindow::dispImg()
{

    ui->progressBar->setValue(40);
    ui->progressBar->setFormat(QStringLiteral("%p%显示图像,等待处理"));
    ui->progressBar->repaint();
    switch(ui->base->currentIndex())
    {
        case 0:

            break;
        case 1:
            profile->getVideoFrame();

            break;
        case 2:
            profile->getSingleFrame();
            break;
        case 3:
            hal->disp_img();
            break;
    }



    ui->startButton->setEnabled(true);
    ui->action_start->setEnabled(true);
    if(isAuto&isRunning)
    {
        ui->progressBar->setValue(60);
        ui->progressBar->setFormat(QStringLiteral("%p%处理中."));
        ui->progressBar->repaint();
        emit detect();

    }
}
/*
    函数名:wheelEvent
    参数:event为鼠标滑轮的事件指针
    返回值:无
    作用:
    触发鼠标滑轮时会执行到这里的代码
*/
void MainWindow::wheelEvent(QWheelEvent *event)
{

    QPoint m=mapFromGlobal(event->globalPos());

    if(QRect(ui->view_box->pos().x()+ui->base->pos().x(),ui->view_box->pos().y()+ui->base->pos().y(),ui->base->width()
             ,ui->base->height()).contains(m))
    {
        if(event->delta()>0)
        {
            controlImg(5);

        }
        if(event->delta()<0)
        {
            controlImg(4);

        }

    }
    event->accept();      //接收该事件

}

/*
    函数名:searchFile
    参数:path为需要搜索的路径名,即文件夹所在
    返回值:无
    作用:

*/
void MainWindow::searchFile(QString path)
{
    qDebug()<<"searchFile"<<path;
    fileList.clear();
    QDir dir;
    QStringList filters;
    filters <<"*.jpg"<<"*.bmp"<<"*.png";
    dir.setPath(path.toUtf8().data());
    dir.setNameFilters(filters);
    dir.setSorting(QDir::Name);
    if(!dir.exists())
    {
        QMessageBox::warning(this,QStringLiteral("错误"),QStringLiteral("目录不存在,请设置正确的文件路径"));
        return;
    }

    QDirIterator iter(dir,QDirIterator::Subdirectories);

    while (iter.hasNext())
    {
        iter.next();

        QFileInfo info=iter.fileInfo();

        if (info.isFile())
        {

          //  QListWidgetItem *item=new QListWidgetItem(info.fileName());

            fileList.append(info.filePath());

        }
        if(info.isDir())
            searchFile(info.fileName());
    }
}


void MainWindow::detect()
{

  //  (hal->*(hal->menu[8]))();
   (hal->*hal->menu[8])();
    //QMessageBox::about(this,QStringLiteral("别急"),QStringLiteral("请先打开需要检测的文件~"));

    ui->progressBar->setValue(100);
    ui->progressBar->setFormat(QStringLiteral("%p%完成"));
    ui->progressBar->repaint();
    if(isAuto&isRunning)
    {
            if(index<fileList.size()-1)
            {
                index++;

            }
            else
            {
                index=0;
                emit startButton_clicked();
            }

            selectImg(index);

    }
}
/*
    函数名:startButton_clicked
    参数:无
    返回值:无
    作用:
    当点击开始检测后,进入此处

*/
void MainWindow::startButton_clicked()
{
   if(isRealTime)
   {
       switch(ui->base->currentIndex())
       {
            case 1:
                stopVideo();
                break;
            case 2:
                stopSingleFrame();
                break;
       }
       return;
   }
   if(isAuto)
   {
        if(!isRunning)
        {
            ui->startButton->setText(QStringLiteral("停止检测"));
            isRunning=true;
            emit selectImg(index);
        }
        else
        {
            ui->startButton->setText(QStringLiteral("开始检测"));
            isRunning=false;
        }
   }
   else
   {
       QTime time;
       time.start();
       switch(ui->base->currentIndex())
       {
            case 0:

                break;
           case 1:

               break;
           case 2:

               break;
           case 3:
               hal->open_the_window(ui->base->winId(),ui->base->width(),ui->base->height());
               profile->GetProfiles_Callback();
               break;
       }

       qDebug()<<QStringLiteral("扫描时间:")<<time.elapsed()<<"msec";
   }

}

MainWindow::~MainWindow()
{

    delete ui;

}
/*
    函数名:CloseEvent
    参数:e为关闭事件的指针
    返回值:无
    作用:
    拦截关闭事件,弹出退出提示信息

*/
void MainWindow::closeEvent(QCloseEvent *e)
{

    if(QMessageBox::Yes == QMessageBox::question(this,QStringLiteral("提示"),QStringLiteral("你确定要关闭?"),
                                                 QMessageBox::Yes | QMessageBox::No)){
        //d_plot->populate_clear();
        e->accept();

    }
    else{
        e->ignore();
    }

}
/*
    函数名:Net_Param
    参数:无
    返回值:无
    作用:
    弹出网络设置对话框

*/
void MainWindow::Net_Param()
{
    dialNet->show();
    if(dialNet->exec() == QDialog::Accepted)
    {
        qDebug()<<"Accepted";
    }
}
/*
    函数名:about
    参数:无
    返回值:无
    作用:
    弹出关于对话框

*/
void MainWindow::about()
{

    QMessageBox::about(this,QStringLiteral("关于"),("reflectcontrol by bingone    "));

}

/*
    退出按键
*/
void MainWindow::on_action_Quit_triggered()
{
    this->close();
}



/*
    函数名:controlImg
    参数:index
    返回值:无
    作用:
    根据index选择对图像的控制

*/
void MainWindow::controlImg(int index)
{
    switch(index)
    {
        case 0:
            hal->moveImg(0,100);
            hal->set_pos(0,100);
            break;
        case 1:
            hal->moveImg(0,-100);
            hal->set_pos(0,-100);
            break;
        case 2:
            hal->moveImg(100,0);
            hal->moveImg(100,0);
            break;
        case 3:
            hal->moveImg(-100,0);
            hal->moveImg(-100,0);
            break;
        case 4:
            hal->zoomOut();
            break;
        case 5:
            hal->zoomIn();
            break;
        case 6:
            hal->reset();
            break;
    }

}

void MainWindow::readSettings()
{
    filePath=set.value("path","D:/image").toString();
}



void MainWindow::on_textChanged()
{
    preIndex=-1;
}
void MainWindow::netTest(QString str)
{
    ref->initSocked(set.value("photpIp").toString(),set.value("udpPort").toInt());
    ref->sendMsg(str,set.value("photoIp").toString(),set.value("photoPort").toInt());

}

void MainWindow::on_loadFile_clicked()
{

    ui->progressBar->setValue(20);
    ui->progressBar->setFormat(QStringLiteral("%p%加载文件中.."));
    ui->progressBar->repaint();
     hal->open_the_window(ui->base->winId(),ui->base->width(),ui->base->height());
    hal->read_img("data/Z.mtx");
}




void MainWindow::on_test_clicked()
{
    point->show();
}
void MainWindow::paintEvent(QPaintEvent *event)
{

    event->accept();
    //hal->disp_img();

}
void MainWindow::on_launchDevice_clicked()
{
    ui->progressBar->setValue(20);
    ui->progressBar->setFormat(QStringLiteral("%p%读取激光数据中.."));
    ui->progressBar->repaint();

    profile->initDevice();
    ui->startButton->setEnabled(true);
}
void MainWindow::outputMessage(QtMsgType type,QString str)
{
    ui->debug->appendPlainText(str);
}

void MainWindow::on_setPoint_clicked()
{
    if(isDrawing)
    {
        isDrawing=false;
        ui->setPoint->setText(QStringLiteral("绘制测量点"));
    }
    else
    {
        ui->setPoint->setText(QStringLiteral("停止绘制"));
        isDrawing=true;
        hal->clearRect();
        hal->RectHeightSub();

    }

}
void MainWindow::recvHeightSub(double x,double y,double x2,double y2,double min,double max)
{
    static double tempMin,tempMax;
    if(ui->check_num->value()!=1)
    {
        ui->check_num->setValue(ui->check_num->value()-1);
        tempMin=tempMin<min?tempMin:min;
        tempMax=tempMax>max?tempMax:max;
        hal->RectHeightSub();
        return;
    }
    else
        {
        tempMin=min;
        tempMax=max;
    }
    ui->tableWidget->setSortingEnabled(false);
    sum->add_row();
    if((tempMax-tempMin)>ui->limitValue->text().toDouble())
        sum->add_item(0,QString("NG"));
    sum->add_item(1,QString("%1,%2").arg(x).arg(y));
    sum->add_item(2,QString("%1,%2").arg(x2).arg(y2));
    sum->add_item(3,QString("%1").arg(tempMin));
    sum->add_item(4,QString("%1").arg(tempMax));
    sum->add_item(5,QString("%1").arg(tempMax-tempMin));

    isDrawing=false;
    ui->setPoint->setText(QStringLiteral("绘制测量点"));
    ui->tableWidget->setSortingEnabled(true);
}

void MainWindow::on_actionReset_triggered()
{
    sum->clear_table();
}

void MainWindow::on_tableWidget_cellClicked(int row, int column)
{
    qDebug()<<row<<column;
}

void MainWindow::on_realTimeButton_clicked()
{
    hal->close_the_window();
    ui->base->setCurrentIndex(1);
    startVideo();

}
void MainWindow::startVideo()
{
    stopSingleFrame();
    isRealTime=true;
    connect(timer,SIGNAL(timeout()),this,SLOT(dispImg()));
    ui->startButton->setText(QStringLiteral("停止"));
    profile->startVedio();
    timer->start(1000);

}
void MainWindow::stopVideo()
{
    if(!isRealTime)
        return;
    isRealTime=false;
    timer->stop();
    ui->startButton->setText(QStringLiteral("开始扫描"));
    disconnect(timer,SIGNAL(timeout()),this,SLOT(dispImg()));
    profile->stopVedio();
}
void MainWindow::startSingleFrame()
{
    stopVideo();
    isRealTime=true;
    connect(timer,SIGNAL(timeout()),this,SLOT(dispImg()));
    ui->startButton->setText(QStringLiteral("停止"));
    timer->start(40);
    profile->startSingleFrame();
}
void MainWindow::stopSingleFrame()
{
    if(!isRealTime)
        return;
    isRealTime=false;
    timer->stop();
    ui->startButton->setText(QStringLiteral("开始扫描"));
    disconnect(timer,SIGNAL(timeout()),this,SLOT(dispImg()));
    profile->stopSingleFrame();
}
void MainWindow::on_singleFrameButton_clicked()
{

    hal->close_the_window();
    ui->base->setCurrentIndex(2);
    startSingleFrame();
}

void MainWindow::on_threeDButton_clicked()
{
     stopVideo();
     stopSingleFrame();
     hal->open_the_window(ui->base->winId(),ui->base->width(),ui->base->height());
     ui->base->setCurrentIndex(0);
     hal->setMode("3D");
}

void MainWindow::on_twoDButton_clicked()
{
    stopVideo();
    stopSingleFrame();
    hal->open_the_window(ui->base->winId(),ui->base->width(),ui->base->height());
    ui->base->setCurrentIndex(3);
    hal->setMode("2D");
}
