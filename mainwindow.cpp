#include "mainwindow.h"
#include "ui_mainwindow.h"




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
    isRealTime=false;
    leftRightPress=false;
    leftPress=false;
    rightPress=false;
    index=0;
    status=0;
    pass=0;
    preIndex=-1;

    //profile=new profileGet();
    //kings=new kingsControl();
    //laser=new kingsControl();


    debug.setFileName("debug.txt");
    debug.open(QIODevice::Append);
    out.setFileName("data.txt");
    out.open(QIODevice::Append);
    // plot = new Plot(ui->base->widget(2));
    QStringList str;
    str<<"value"<<"pointNum"<<"1280"<<"100";

    // plot->initPlot(str);
    // plot->insertCurve(0,0,"test");
    // plot->setYScale(-100,100);
    // plot->setXScale(-40,40);
    // plot->resize(ui->base->widget(2)->size());
    imgView=new imgListView();
    imgView->setHBoxLayout(ui->imgList);

    //qDebug()<<settings::team::roiList::roi.name;

    timer=new QTimer();
    eventTimer=new QTimer();
    connect(eventTimer,SIGNAL(timeout()),this,SLOT(statusCheck()));
    eventTimer->start(10);
    sum=new summarizing;
    sum->set_table(ui->tableWidget);
    roiList=new summarizing;
    roiList->set_table(ui->roiList);

    mygroup = new QButtonGroup;
    mygroup->addButton(ui->imgUp,0);
    mygroup->addButton(ui->imgDown,1);
    mygroup->addButton(ui->imgLeft,2);
    mygroup->addButton(ui->imgRight,3);
    mygroup->addButton(ui->imgBig,4);
    mygroup->addButton(ui->imgSmall,5);
    mygroup->addButton(ui->imgRotate,6);

    ui->progressBar->setMaximum(100);
    palette=ui->videoFrame->palette();
    pointData=new pointDataDialog;

    ui->videoFrame->setAutoFillBackground(true);

    delItem=new QAction(QStringLiteral("删除"),this);
    modifyItem=new QAction(QStringLiteral("修改"),this);
    delAllItem=new QAction(QStringLiteral("全部删除"),this);
    connect(delItem,SIGNAL(triggered()),this,SLOT(action_delItem()));
    connect(modifyItem,SIGNAL(triggered()),this,SLOT(action_modifyItem()));
    connect(delAllItem,SIGNAL(triggered()),this,SLOT(action_delAllItem()));
    //加载检测查块
    hal=new halconClass;
    ref=new reflectControl;
    robot=new Robot;
    robot->initSocked(set.value("robotIp","127.0.0.1").toString(),set.value("robotPort",4000).toInt());
    // glWidget = new GLWidget;
    // QGridLayout *layout=new QGridLayout;
    // layout->addWidget(glWidget);
    //ui->base->setLayout(layout);
    //  writeData = new writeExcel;

    //设置对话框
    setDialog = new mySettings;
    setDialog->setModal(true);
    pointData=new pointDataDialog();

    point=new pointAnalyze;

    //激活鼠标跟踪功能
    setMouseTracking(true);
    ui->centralWidget->setMouseTracking(true);
    ui->base->setMouseTracking(true);
    ui->base->installEventFilter(this);
    ui->view_box->installEventFilter(this);
    ui->roiList->installEventFilter(this);
    ui->imgList->installEventFilter(this);
    //glWidget->setMouseTracking(true);

    init_connect();

    hal->open_the_window(ui->base->winId(),ui->base->width(),ui->base->height());
}
void MainWindow::initLaser()
{

    if(!set.value("kingsCheck",false).toBool())
    {
        if(laser!=profileGet::profileInstance())
            laser=profileGet::profileInstance();

    }
    else
    {
        if(laser!=kingsControl::kingsInstance())
            laser=kingsControl::kingsInstance();
    }
    disconnect(ui->actionStop,SIGNAL(triggered()),laser,SLOT(stopGetData()));
    disconnect(hal,SIGNAL(reConnect()),laser,SLOT(startGetData()));
    disconnect(laser,SIGNAL(putImagebyPointer1(double*,int,int)),hal,SLOT(getImagebyPointer1(double*,int,int)));
    disconnect(laser,SIGNAL(heartPack()),this,SLOT(recvHeartPack()));
    disconnect(laser,SIGNAL(Error(QString)),this,SLOT(Error(QString)));
    connect(ui->actionStop,SIGNAL(triggered()),laser,SLOT(stopGetData()));
    connect(hal,SIGNAL(reConnect()),laser,SLOT(startGetData()));
    connect(laser,SIGNAL(putImagebyPointer1(double*,int,int)),hal,SLOT(getImagebyPointer1(double*,int,int)));
    connect(laser,SIGNAL(heartPack()),this,SLOT(recvHeartPack()));
    connect(laser,SIGNAL(Error(QString)),this,SLOT(Error(QString)));
}
bool MainWindow::eventFilter(QObject *target, QEvent *event)
{
    static QPoint start,end,threeDstart,threeDend,hps,hpe;

    if (clickLabel* label = dynamic_cast<clickLabel*>(sender())){
        qDebug()<<ui->imgList->indexOf(label);
    }
    if(target==ui->base)
    {


        if(event->type()==QEvent::MouseButtonPress)
        {

            QMouseEvent *mouse=static_cast<QMouseEvent *>(event);

            if(mouse->button()==Qt::LeftButton)
                leftPress=true;
            if(mouse->button()==Qt::RightButton)
                rightPress=true;
            threeDstart=start=hal->getPoint();

            ui->pos->setText(QString("%1,%2").arg(start.x()).arg(start.y()));
            isDrag=true;

        }

        if(event->type()==QEvent::MouseMove)
        {
            QMouseEvent *mouse=static_cast<QMouseEvent *>(event);

            QPoint m=mapFromGlobal(mouse->globalPos());


            QPoint mp=mouse->pos();

            if(mp.x()<10|mp.y()<30|mp.x()>ui->base->width()-10|mp.y()>ui->base->height()-30)
                return QWidget::eventFilter(target,event);
            if(!isDrawing)
                end=hal->getPoint();

            //ui->pos->setText(QString("%1,%2").arg(end.x()).arg(end.y()));
            //start=mouse->pos();
            if(isDrag)
            {
                int x,y;
                x=end.x()-threeDstart.x();
                y=end.y()-threeDstart.y();
                if(!isDrawing)
                {
                    hal->moveImg(threeDstart.x()-end.x(),threeDstart.y()-end.y());
                    ui->view_box->update();
                    if(leftPress&rightPress)
                    {
                        //  hal->threedControl(end.x(),end.y(),threeDstart.x(),threeDstart.y(),"move");
                        hal->threedControl(threeDstart.y(),threeDstart.x(),end.y(),end.x(),"move");
                    }
                    else if(leftPress)
                    {

                        //   hal->threedControl(end.y(),end.x(),threeDstart.y(),threeDstart.x(),"rotate");
                        hal->threedControl(threeDstart.y(),threeDstart.x(),end.y(),end.x(),"rotate");

                    }
                    else if(rightPress)
                    {
                        //  hal->threedControl(end.x(),end.y(),threeDstart.x(),threeDstart.y(),"scale");
                        hal->threedControl(threeDstart.x(),threeDstart.y(),end.x(),end.y(),"scale");

                    }
                    threeDstart=end;
                }
            }

        }
        if(event->type()==QEvent::MouseButtonRelease)
        {
            QMouseEvent *mouse=static_cast<QMouseEvent *>(event);
            QPoint m=mapFromGlobal(mouse->globalPos());
            QPoint mp=mouse->pos();


            if(mp.x()<10|mp.y()<30|mp.x()>ui->base->width()-10|mp.y()>ui->base->height()-30)
                return QWidget::eventFilter(target,event);
            if(!isDrawing)
                end=hal->getPoint();

            isDrag=false;
            if(mouse->button()==Qt::LeftButton)
                leftPress=false;
            else if(mouse->button()==Qt::RightButton)
                rightPress=false;
            if(!isDrawing)
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
    else if(target==ui->roiList)
    {
        if(event->type()==QEvent::ContextMenu)
        {
            QContextMenuEvent *mouse=static_cast<QContextMenuEvent *>(event);

            int height=ui->roiList->horizontalHeader()->height();
            QPoint pt=mouse->pos();
            QPoint pt2=QPoint(0,height);

            currentItem=ui->roiList->indexAt(pt-pt2).row();

            qDebug()<<mouse->pos();
            qDebug()<<pt-pt2;
            qDebug()<<"item"<<currentItem;
            QMenu menu(this);

            menu.addAction(delItem);
            menu.addAction(modifyItem);
            menu.addAction(delAllItem);
            menu.exec(mouse->globalPos());
        }
        return QWidget::eventFilter(target,event);
    }
    else
        return  QWidget::eventFilter(target,event);

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
    connect(pointData,SIGNAL(addRoi(QMap<QString,QVariant>)),hal,SLOT(drawRect(QMap<QString,QVariant>)));
    connect(ui->action_big,SIGNAL(triggered()),hal,SLOT(zoomOut()));
    connect(ui->action_small,SIGNAL(triggered()),hal,SLOT(zoomIn()));
    connect(ui->reset,SIGNAL(clicked()),this,SLOT(on_actionReset_triggered()));
    //点击开始按钮
    connect(ui->action_start,SIGNAL(triggered()),this,SLOT(startButton_clicked()));
    //读取文件按钮
    connect(ui->action_Open,SIGNAL(triggered()),this,SLOT(on_loadFile_clicked()));
    connect(ui->actionTest,SIGNAL(triggered()),hal,SLOT(test()));
    connect(ui->actionCal,SIGNAL(triggered()),hal,SLOT(calculate()));
    connect(ui->action_init,SIGNAL(triggered()),this,SLOT(on_launchDevice_clicked()));
    //connect(ui->actionCallback,SIGNAL(triggered()),profile,SLOT(start()));

    //connect(point,SIGNAL(initDevice()),profile,SLOT(initDevice()));

    //触发设置窗口
    connect(ui->settings,SIGNAL(clicked()),ui->action_Net_Param,SLOT(trigger()));
    connect(ui->settings,SIGNAL(clicked()),this,SLOT(on_textChanged()));
    connect(setDialog,SIGNAL(openFile(QString)),this,SLOT(openFile(QString)));
    connect(mygroup,SIGNAL(buttonClicked(int)),this,SLOT(controlImg(int)));
    connect(ref,SIGNAL(recvData(char*)),setDialog,SLOT(recvData(char*)));
    //connect(ui->roiColor,SIGNAL(clicked()),this,SLOT(on_roiColor_clicked()));


    connect(MsgHandlerWapper::instance(),SIGNAL(message(QtMsgType,QString)),this,
            SLOT(outputMessage(QtMsgType,QString)));
    //接收显示信号
    //connect(hal,SIGNAL(clearMemory()),laser,SLOT(clearMemory()));
    connect(hal,SIGNAL(dispImg()),this,SLOT(dispImg()));
    connect(hal,SIGNAL(Warning(QString)),this,SLOT(Warning(QString)));
    connect(hal,SIGNAL(sendPlaneness(int,double)),this,SLOT(recvPlaneness(int,double)));
    connect(hal,SIGNAL(flushRoiList(QStringList)),this,SLOT(flushRoiList(QStringList)));
    connect(hal,SIGNAL(Error(QString)),this,SLOT(Error(QString)));
    connect(hal,SIGNAL(sendHeightSub(QString,double,double,double))
            ,this,SLOT(recvHeightSub(QString,double,double,double)));

    // connect(kings,SIGNAL(dispSingleFrame(unsigned short*,unsigned short*,double*,double*,int)),
    //        plot,SLOT(upScanControlData(unsigned short*,unsigned short*,double*,double*,int)));

    //connect(profile,SIGNAL(putImagebyPointer1(double*,int,int)),hal,SLOT(getImagebyPointer1(double*,int,int)));
    //connect(profile,SIGNAL(putImagebyPointer3(double*,double*,double*,int,int)),hal,SLOT(getImagebyPointer3(double*,double*,double*,int,int)));
    //connect(profile,SIGNAL(setData(double*,int)),glWidget,SLOT(setData(double*,int)));
    //connect(profile,SIGNAL(Error(QString)),this,SLOT(Error(QString)));

    //connect(profile,SIGNAL(dispFrame(unsigned char*,int)),this,SLOT(dispFrame(unsigned char*,int)));
    //connect(profile,SIGNAL(heartPack()),this,SLOT(recvHeartPack()));
    //connect(profile,SIGNAL(dispSingleFrame(unsigned short *,unsigned short *,double *,double *,int)),
    //        plot,SLOT(upScanControlData(unsigned short *,unsigned short *,double *,double *,int)));

    //connect(ui->actionTest,SIGNAL(triggered()),hal,SLOT(RectHeightSub()));

    //connect(setDialog,SIGNAL(selectDevice(int)),profile,SLOT(selectDevice(int)));
    //connect(setDialog,SIGNAL(postExposeTime(int,int)),profile,SLOT(setExposeTime(int ,int )));

   // connect(setDialog,SIGNAL(setExternTrigger(int)),profile,SLOT(setExternTrigger(int)));
    //connect(setDialog,SIGNAL(updataSettings()),profile,SLOT(flushSettings()));
    connect(setDialog,SIGNAL(netTest(QString)),this,SLOT(netTest(QString)));
    connect(setDialog,SIGNAL(upDataNetwork(QString,int)),robot,SLOT(initSocked(QString,int)));
    connect(hal,SIGNAL(addImg(Hobject*)),imgView,SLOT(addImg(Hobject*)));
    connect(hal,SIGNAL(deleteImg(int )),imgView,SLOT(deleteImg(int )));
    connect(hal,SIGNAL(deleteAllImg()),imgView,SLOT(deleteAllImg()));
    connect(imgView,SIGNAL(selectImg(int)),hal,SLOT(selectImg(int)));
    initLaser();
}

void MainWindow::Error(QString str)
{

    QMessageBox::warning(this,
                         QStringLiteral("错误"),
                         str,
                         QMessageBox::Yes );
}
void MainWindow::Warning(QString str)
{
    ui->prompt->setText(str);
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
    palette.setBrush(QPalette::Window,QBrush(
                         QImage::fromData(buf,size).scaled(ui->videoFrame->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));

    ui->videoFrame->setPalette(palette);
}
/*
    显示控制
*/
void MainWindow::dispImg()
{

    status=0;

    switch(ui->base->currentIndex())
    {
    case 0:
        status=3;
        hal->disp_img();
        break;
    case 1:
        //profile->getVideoFrame();
        palette.setBrush(QPalette::Window,QBrush(
                             QImage("frame.bmp").scaled(ui->videoFrame->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));

        ui->videoFrame->setPalette(palette);
        break;
    case 2:
        //profile->getSingleFrame();
        break;
    case 3:
        status=3;
        hal->disp_img();
        //hal->RectHeightSub();
        break;
    }



    ui->startButton->setEnabled(true);
    ui->action_start->setEnabled(true);
    if(isAuto&isRunning)
    {

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
    if(isDrawing)
        return;
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
    qDebug()<<"start";
    this->on_actionReset_triggered();
    //hal->RectHeightSub();
    pass=0;
    ui->rate->setText("0");

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

        switch(ui->base->currentIndex())
        {
        case 0:
            //profile->startTrigger();
            break;
        case 1:
           // profile->startVideo();
            break;
        case 2:
            laser->startGetData();
            //profile->startSingleFrame();
            break;
        case 3:
            status=2;
            hal->open_the_window(ui->base->winId(),ui->base->width(),ui->base->height());
            //profile->GetProfiles_Callback();
            //profile->start();
            //profile->startTrigger();
            laser->startGetData();

            break;
        }


    }

}

MainWindow::~MainWindow()
{
    eventTimer->stop();
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
    setDialog->flush_settings();
    setDialog->show();

    if(setDialog->exec() == QDialog::Accepted)
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
    if(isDrawing)
        return;
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
        hal->set_pos(100,0);
        break;
    case 3:
        hal->moveImg(-100,0);
        hal->set_pos(-100,0);
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
/*
    读取配置
*/
void MainWindow::readSettings()
{
    filePath=set.value("path","D:/image").toString();
}



void MainWindow::on_textChanged()
{
    preIndex=-1;
}
/*
    通过socket发送消息,以测试连接
*/
void MainWindow::netTest(QString str)
{
    ref->initSocked(set.value("photpIp").toString(),set.value("udpPort").toInt());
    ref->sendMsg(str,set.value("photoIp").toString(),set.value("photoPort").toInt());

}
/*
    读取测试文件

*/
void MainWindow::on_loadFile_clicked()
{
    status=1;

    hal->open_the_window(ui->base->winId(),ui->base->width(),ui->base->height());
    hal->read_img(set.value("path","test.tif").toString());

}
void MainWindow::openFile(QString path)
{
    status=1;

    hal->open_the_window(ui->base->winId(),ui->base->width(),ui->base->height());
    hal->read_img(path);
}




void MainWindow::paintEvent(QPaintEvent *event)
{

    event->accept();
    //hal->disp_img();

}
/*
    启动并初始化激光
*/
void MainWindow::on_launchDevice_clicked()
{


    //profile->initDevice();
    initLaser();
    laser->initDevice();

    ui->startButton->setEnabled(true);
    ui->action_start->setEnabled(true);
}
/*


    接收Debug信息并重定向到某控件上,文件上
*/
void MainWindow::outputMessage(QtMsgType type,QString str)
{
    QTime time;
    str=time.currentTime().toString("hh:mm:ss.zzz: ")+str;

    setDialog->debugMessage(str);
    debug.write((str+"\n").toUtf8().data());

    debug.flush();
}

/*
 *  name:recvHeightSub
    type:槽函数
    arg:[1]:int为分组,QString为区域名
        [2]:高差最小值
        [3]:高差最大值
        [4]:高差

    disciption:
        接收高差计算结果并显示

*/
void MainWindow::recvHeightSub(int,double min,double max,double range)
{}
void MainWindow::recvHeightSub(QString name,double min1,double max1,double range)
{
    status=0;
    int i;
    double min,max;
    QMap<QString,QVariant> data=set.value("dataList").toMap();
    for(i=0;i<data.keys().size();i++)
    {
        if(data.value(data.keys().at(i)).toStringList().contains(name))
            break;
    }
    ui->tableWidget->setSortingEnabled(false);
    sum->add_row();
    QMap<QString,QVariant> roi=set.value("team/"+name).toMap();
    min=roi.value("min").toDouble();
    max=roi.value("max").toDouble();

    out.write(QTime::currentTime().toString().toUtf8()+',');
    if(range<min|range>max)
    {
        sum->add_item(0,QString("NG"));

        ui->connect->setText(QStringLiteral("NG!"));
        ui->connect->setStyleSheet(QString::fromUtf8("font: 18pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
                                                  "color: rgb(255, 0, 0);"));
        out.write("NG,");
    }
    else
    {
        sum->add_item(0,QString("OK"));
        ui->connect->setText(QStringLiteral("OK!!"));
        ui->connect->setStyleSheet(QString::fromUtf8("font: 18pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
                                                   "color: rgb(0, 0, 0);"));
        out.write("OK,");
    }
    sum->add_item(1,QStringLiteral("高差"));
    out.write(QString(QStringLiteral("高差")+',').toUtf8());
    sum->add_item(2,QStringLiteral("分组")+QString::number(i+1));
    out.write(QString(QStringLiteral("分组")+QString::number(i+1)+',').toUtf8());
    sum->add_item(3,name);
    out.write((name+',').toUtf8());
    sum->add_item(4,QString("%1").arg(range));
    out.write(QString("%1\r\n").arg(range).toUtf8());




    ui->tableWidget->setSortingEnabled(true);
     ui->tableWidget->setCurrentCell(ui->tableWidget->rowCount()-1,0);
    out.flush();
}

/*
 *  name:recvPlaneness
    type:槽函数
    arg:[1]:int为分组
        [2]:结果1
        [3]:结果2

    disciption:
        接收高差计算结果并显示

*/
void MainWindow::recvPlaneness(int team,double result1)
{
    status=0;
    QStringList datastring;


    QMap<QString,QVariant> data=set.value("dataList").toMap();

    ui->tableWidget->setSortingEnabled(false);
    sum->add_row();
    QMap<QString,QVariant> map=set.value("limit").toMap();
    QStringList str=map.value(QString::number(team)).toStringList();
    double min=str.size()>0?str.at(0).toDouble():0;
    double max=str.size()>0?str.at(1).toDouble():0;
    out.write(QTime::currentTime().toString().toUtf8()+',');
    if(result1<min|result1>max)
    {
        sum->add_item(0,QString("NG"));

        out.write(QByteArray("NG,"));
        ui->connect->setText(QStringLiteral("NG!"));
        ui->connect->setStyleSheet(QString::fromUtf8("font: 18pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
                                                     "color: rgb(255, 0, 0);"));
    }
    else
    {
        sum->add_item(0,QString("OK"));
        ui->connect->setText(QStringLiteral("OK!!"));
        ui->connect->setStyleSheet(QString::fromUtf8("font: 18pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
                                               "color: rgb(0, 0, 0);"));
        out.write(QByteArray("OK,"));
    }
    sum->add_item(1,QStringLiteral("平面度"));
    out.write(QString(QStringLiteral("平面度")+',').toUtf8());
    sum->add_item(2,QStringLiteral("分组")+QString::number(team+1));
    out.write(QString(QStringLiteral("分组")+QString::number(team+1)+',').toUtf8());
    sum->add_item(3,"N/A");
    out.write("N/A,");
    sum->add_item(4,QString("%1").arg(result1));
    out.write(QString("%1\r\n").arg(result1).toUtf8());

    //sum->add_item(7,QString("%1,%2").arg(str.at(2)).arg(str.at(1)));

    ui->tableWidget->setSortingEnabled(true);
    ui->tableWidget->setCurrentCell(ui->tableWidget->rowCount()-1,0);
    out.flush();
}
/*
    清除表格,测试用
*/
void MainWindow::on_actionReset_triggered()
{
    pass=0;
    sum->clear_table();

    hal->clearData();
}

void MainWindow::on_tableWidget_cellClicked(int row, int column)
{

}
/*
    切换为视频模式
*/
void MainWindow::on_realTimeButton_clicked()
{
    hal->close_the_window();
    ui->base->setCurrentIndex(1);
    //startVideo();

}
/*
    开始视频模式
*/
void MainWindow::startVideo()
{
    stopSingleFrame();

    connect(timer,SIGNAL(timeout()),this,SLOT(dispImg()));

    //profile->startVideo();
    timer->start(200);

}
void MainWindow::stopVideo()
{

    timer->stop();
    ui->startButton->setText(QStringLiteral("开始扫描"));
    disconnect(timer,SIGNAL(timeout()),this,SLOT(dispImg()));

}
/*
    停止视频模式
*/
void MainWindow::startSingleFrame()
{
    stopVideo();

    connect(timer,SIGNAL(timeout()),this,SLOT(dispImg()));

    timer->start(200);
    //profile->startSingleFrame();
}
/*
    停止单帧模式
*/
void MainWindow::stopSingleFrame()
{

    timer->stop();
    ui->startButton->setText(QStringLiteral("开始扫描"));
    disconnect(timer,SIGNAL(timeout()),this,SLOT(dispImg()));

}
/*
    开始单帧模式
*/
void MainWindow::on_singleFrameButton_clicked()
{

    hal->close_the_window();
    ui->base->setCurrentIndex(2);
    laser->setDispMode(0);
    //startSingleFrame();
}
/*
    3D模式按钮事件
*/
void MainWindow::on_threeDButton_clicked()
{

    hal->open_the_window(ui->base->winId(),ui->base->width(),ui->base->height());
    //stopSingleFrame();
    ui->startButton->setText(QStringLiteral("开始扫描"));
    ui->base->setCurrentIndex(0);
    // profile->startTrigger();
    hal->setMode("3D");
}
/*
    2D模式按钮事件
*/
void MainWindow::on_twoDButton_clicked()
{

    hal->open_the_window(ui->base->winId(),ui->base->width(),ui->base->height());
    //stopSingleFrame();
    ui->startButton->setText(QStringLiteral("开始扫描"));
    //profile->startTrigger();
    laser->setDispMode(1);
    ui->base->setCurrentIndex(3);
    hal->setMode("2D");
}

/*
    绘图按钮事件
*/
void MainWindow::on_roiDraw_clicked()
{
    if(isDrawing)
        return;
    isDrawing=true;
    double min,max;
    min=ui->minValue1->text().toDouble();
    max=ui->maxValue1->text().toDouble();
    if(min>max)
    {
        double tmp=min;
        min=max;
        max=tmp;
        ui->minValue1->setText(QString::number(min));
        ui->maxValue1->setText(QString::number(max));
    }
    QMap<QString,QVariant> map,limit;
    map.insert("Row",ui->pointY->value());
    map.insert("Column",ui->pointX->value());
    map.insert("unit",ui->unit->currentIndex());
    map.insert("Length1",ui->roiLength1->value());
    map.insert("Length2",ui->roiLength2->value());
    map.insert("name",ui->roiName->text());
    map.insert("color",ui->roiColor->palette().background().color().rgb());
    map.insert("team",ui->team->currentIndex());
    map.insert("min",ui->minValue1->text());
    map.insert("max",ui->maxValue1->text());
    map.insert("func",ui->func->currentIndex());
    map.insert("drawType",ui->draw1->isChecked()?1:0);
    hal->drawRect(map);

    qDebug()<<ui->roiName->text();
    qDebug()<<ui->roiColor->palette().background().color().rgb()<<ui->team->currentIndex()<<ui->func->currentIndex();
    isDrawing=false;
    if(ui->func->currentIndex()==2)
    {
        QStringList str;

        str<<ui->minValue1->text();
        str<<ui->maxValue1->text();
        limit.insert(QString::number(ui->team->currentIndex()),str);
        set.setValue("limit",limit);
        set.sync();
    }
}
/*
    刷新矩形框列表
*/
void MainWindow::flushRoiList(QStringList ll)
{
    roiList->clear_table();

    ui->roiList->setSortingEnabled(false);
    QStringList line;


    QMap<QString,QVariant> list=set.value("roiList").toMap();
    qDebug()<<"roiList size"<<list.size();
    for(int i=0;i<list.size();i++)
    {
        QMap<QString,QVariant> roi=set.value("team/"+list.keys().at(i)).toMap();

        roiList->add_row();
        roiList->add_item(0,list.keys().at(i));

        roiList->add_item(1,QString::number(roi.value("team").toInt()+1));
        switch(roi.value("func").toInt())
        {
        case 0:
            roiList->add_item(2,QStringLiteral("定位"));
            break;
        case 1:
            roiList->add_item(2,QStringLiteral("搜索"));
            break;
        case 2:
            roiList->add_item(2,QStringLiteral("定基准点"));

            break;
        case 3:
            roiList->add_item(2,QStringLiteral("计算平面度"));         
            break;
        case 4:
            roiList->add_item(2,QStringLiteral("点到平面高差"));
            break;
        case 5:
            roiList->add_item(2,QStringLiteral("点到点高差"));
            break;
        }
        switch(roi.value("func").toInt())
        {
        case 2:
        case 3:
        case 4:
        case 5:
            roiList->add_item(3,roi.value("min").toString());
            roiList->add_item(4,roi.value("max").toString());
            if(roi.value("isDraw").toInt()==0)
                ui->lableXY->setText(QString("%1,%2").arg(roi.value("x").toFloat()).arg(roi.value("y").toFloat()));
            break;
        }


    }
    ui->roiList->setSortingEnabled(true);
}
/*
    矩形框列表删除事件
*/
void MainWindow::action_delItem()
{



    if(currentItem==-1)
        return;
    QString name=ui->roiList->item(currentItem,0)->text();
    ui->roiList->removeRow(currentItem);
    ui->roiList->update();
    hal->delRect(name);
}
void MainWindow::action_delAllItem()
{
    int i,maxrow = ui->roiList->rowCount();

    for(i=maxrow-1;i>=0;i--)
    {
        QString name=ui->roiList->item(i,0)->text();
        hal->delRect(name);
        ui->roiList->removeRow(i);
    }
}
/*
    矩形框列表修改事件
*/
void MainWindow::action_modifyItem()
{
    QMap<QString,QVariant> list=set.value("roiList").toMap();
    QStringList tmp=list.keys();
}
/*
    状态检查,暂不完善
*/
void MainWindow::statusCheck()
{
    static int i=0;
    if(laser->testConnect())
    {
        // ui->connect->setText(QStringLiteral("已连接"));
        ui->connect->setStyleSheet(QString::fromUtf8("font: 18pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
                                                     "color: rgb(0, 0, 0);"));
    }
    else
    {
        //ui->connect->setText(QStringLiteral("未连接"));
        ui->connect->setStyleSheet(QString::fromUtf8("font: 18pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
                                                     "color: rgb(255, 0, 0);"));

    }
    if(i>100)
    {
        status=0;
        i=0;
    }
    switch(status)
    {
    case 0:

        updataProsessBar(QStringLiteral("已完成"),100);
        i=0;
        break;
    case 1:
        updataProsessBar(QStringLiteral("读取图像中"),i);
        i+=5;
        break;
    case 2:
        updataProsessBar(QStringLiteral("激光扫描中"),i);
        i+=5;
        break;
    case 3:
        updataProsessBar(QStringLiteral("数据处理中"),i);
        i+=5;
        break;
    }
}
/*
    更新进度条
*/
void MainWindow::updataProsessBar(QString name,int num)
{
    ui->progressBar->setValue(num);
    ui->progressBar->setFormat("%p%"+name+"...");
    ui->progressBar->repaint();
}
/*
    输出excel
*/
void MainWindow::on_toExcel_clicked()
{
    sum->to_excel();
}
void MainWindow::recvHeartPack()
{
    static QTime time;
    pass++;
    ui->rate->setText(QString::number(pass));
    /*
    if(pass%100==0)
        time.start();
    pass++;

    if(pass%100==99&pass!=1)
    {
        double elapsed=time.elapsed();
        ui->rate->setText(QString::number(0.01*elapsed)+"/s fps");
    }
        //ui->rate->setText(QString("%1/s fps").arg(1000/time.elapsed()*100));
        */
}
void MainWindow::on_roiColor_clicked()
{
    QColor color=QColorDialog::getColor();
    if(color.isValid()){
        int r,g,b;
        color.getRgb(&r,&g,&b);
        QString str;
        str=QString("background-color: rgb(%1,%2,%3)").arg(r).arg(g).arg(b);
        ui->roiColor->setStyleSheet(str.toUtf8().data());
        //QPalette pal=ui->roiColor->palette();
        //pal.setColor(QPalette::Active,QPalette::Button, color);
        //ui->roiColor->setPalette(pal);
        qDebug()<<color.rgb();
        qDebug()<<((color.rgb()&(0xff<<16))>>16)<<((color.rgb()&(0xff<<8))>>8)<<(color.rgb()&(0xff));
        ui->roiColor->update();
    }
    //QPalette pal    = ui->roiColor->palette();
    //QBrush brush = pal.background();
    //QColor col      = brush.color();

}






void MainWindow::on_func_currentIndexChanged(int index)
{
    if(index==0|index==1)
    {
        ui->minValue1->setEnabled(false);
        ui->maxValue1->setEnabled(false);
    }
    else
    {
        ui->minValue1->setEnabled(true);
        ui->maxValue1->setEnabled(true);
    }

}

void MainWindow::on_draw1_clicked()
{
    ui->roiLength1->setEnabled(false);
    ui->roiLength2->setEnabled(false);
    ui->pointX->setEnabled(false);
    ui->pointY->setEnabled(false);
    ui->unit->setEnabled(false);
}

void MainWindow::on_draw2_clicked()
{
    ui->roiLength1->setEnabled(true);
    ui->roiLength2->setEnabled(true);
    ui->pointX->setEnabled(true);
    ui->pointY->setEnabled(true);
    ui->unit->setEnabled(true);
}
/*
    读取点位

*/
void MainWindow::on_loadData_clicked()
{

   pointData->show();
}

void MainWindow::on_chart_clicked()
{
    point->show();
}
