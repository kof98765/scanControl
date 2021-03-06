﻿#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "checkthread.h"
#include <QtSerialPort/QSerialPort>
#include "param.h"
#include "filedialog.h"
#include "dialogcameralight.h"
#include "settingDialog.h"
#include "halconclass.h"
#include "dialogimgparam.h"
#include "imgview.h"
#include "imgbase.h"

#include "reflectcontrol.h"
#include "robot.h"
#include "summarizing.h"
#include <QMessageBox>
#include <QCloseEvent>
#include <QDebug>
#include <QPicture>
#include <QPixmap>
#include <QSettings>
#include <QStringListModel>
#include <QWheelEvent>
#include <math.h>
#include <QDirIterator>
#include <QtGui>
#include <QSplashScreen>
#include <QDateTime>
#include "tvplot.h"
#include "ui_data_analyze.h"
#include "pointanalyze.h"
#include "profileget.h"
#include "msghandlerwapper.h"
#include "glwidget.h"
using namespace Halcon;



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void closeEvent(QCloseEvent *e);

public:
    halconClass *hal;
	void init_connect();
    void writeSettings();
    QString filePath;
    void searchFile(QString path);
    void readSettings();

protected:
    void wheelEvent(QWheelEvent *);
    bool eventFilter(QObject *, QEvent *);
    void resizeEvent(QResizeEvent *);
public slots:
    void outputMessage(QtMsgType,QString);
    void recvHeightSub(double,double,double,double,double,double);
    void dispFrame(unsigned char *buf,int size);
    void Net_Param();
    void about();
    void on_action_Quit_triggered();
    void Error(QString error);
    void dispImg();
    void controlImg(int);
    void selectImg(int);
    void modeSelect(int);
    void on_loadFile_clicked();
    void detect();
    void startButton_clicked();
    void netTest(QString);
    void on_textChanged();


    void on_test_clicked();

    void on_launchDevice_clicked();

    void on_setPoint_clicked();

    void on_actionReset_triggered();
    void paintEvent(QPaintEvent *event);

    void on_tableWidget_cellClicked(int row, int column);

    void on_realTimeButton_clicked();

    void on_singleFrameButton_clicked();

    void on_threeDButton_clicked();

    void on_twoDButton_clicked();
    void startVideo();
    void stopVideo();
    void startSingleFrame();
    void stopSingleFrame();
private:
    Ui::MainWindow *ui;
    Plot *plot;
    QDialog *dataDialog;
    profileGet *profile;
    summarizing *sum;
    QButtonGroup *mygroup;
    GLWidget *glWidget;
    QString searchPath;
    QList<QString> fileList;
    QPalette palette;
    DialogNetParam    *dialNet;
    fileDialog *file;
    QLabel *status_label;
    QString serverIp;
    int serverPort;
    QSettings set;
    Robot *robot;
    pointAnalyze *point;
    bool isRunning;
    reflectControl *ref;
    QTimer *timer;
    QString fileName;
    int index;
    int preIndex;
    int pass;
    QPoint currenPos;
    bool isDrag;
    bool isRealTime;
    bool isAuto;
    bool isDrawing;
    bool leftPress;
    bool rightPress;
    bool leftRightPress;
    QList<double> badList;
    int badresult[10];


signals:
    void stopMove();
    void E128_detect();

};

#endif // MAINWINDOW_H
