/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_Net_Param;
    QAction *action_about;
    QAction *action_CameraLight_Param;
    QAction *action_Connection;
    QAction *action_Open;
    QAction *action_Quit;
    QAction *action_imgset;
    QAction *action_start;
    QAction *action_big;
    QAction *action_small;
    QAction *action_EXCEL_T;
    QAction *action;
    QAction *action_pointAnalyze;
    QAction *actionReset;
    QAction *actionTest;
    QAction *action_init;
    QAction *actionCallback;
    QAction *actionSubHeight;
    QAction *action_2;
    QWidget *centralWidget;
    QGroupBox *groupBox_4;
    QPushButton *startButton;
    QPushButton *settings;
    QPushButton *launchDevice;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QPushButton *toExcel;
    QSpacerItem *horizontalSpacer;
    QTableWidget *tableWidget;
    QGroupBox *groupBox_3;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_4;
    QPushButton *roiDraw;
    QFormLayout *formLayout;
    QLabel *label_2;
    QLineEdit *roiName;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_6;
    QComboBox *func;
    QSpacerItem *verticalSpacer_4;
    QLabel *label_4;
    QComboBox *team;
    QSpacerItem *verticalSpacer_3;
    QLabel *label;
    QLineEdit *limitValue;
    QLabel *label_3;
    QSpacerItem *verticalSpacer;
    QPushButton *roiColor;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QTableWidget *roiList;
    QGroupBox *view_box;
    QProgressBar *progressBar;
    QStackedWidget *base;
    QWidget *threeDView;
    QWidget *realTimeView;
    QGridLayout *gridLayout;
    QLabel *videoFrame;
    QWidget *singleFrameView;
    QWidget *twoDView;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *imgLeft;
    QPushButton *imgRight;
    QPushButton *imgUp;
    QPushButton *imgDown;
    QPushButton *imgBig;
    QPushButton *imgSmall;
    QPushButton *imgRotate;
    QPushButton *twoDButton;
    QPushButton *threeDButton;
    QPushButton *realTimeButton;
    QPushButton *singleFrameButton;
    QLabel *rate;
    QLabel *pos;
    QComboBox *comboBox;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *imgList;
    QMenuBar *menuBar;
    QMenu *menu_S;
    QMenu *menu;
    QMenu *menu_2;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1071, 698);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setStyleSheet(QStringLiteral(""));
        action_Net_Param = new QAction(MainWindow);
        action_Net_Param->setObjectName(QStringLiteral("action_Net_Param"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/new/prefix1/ico/graph.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Net_Param->setIcon(icon);
        action_about = new QAction(MainWindow);
        action_about->setObjectName(QStringLiteral("action_about"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/new/prefix1/ico/home.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_about->setIcon(icon1);
        action_CameraLight_Param = new QAction(MainWindow);
        action_CameraLight_Param->setObjectName(QStringLiteral("action_CameraLight_Param"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/new/prefix1/ico/email.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_CameraLight_Param->setIcon(icon2);
        action_Connection = new QAction(MainWindow);
        action_Connection->setObjectName(QStringLiteral("action_Connection"));
        action_Connection->setEnabled(true);
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/new/prefix1/ico/chat_bubble.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Connection->setIcon(icon3);
        action_Open = new QAction(MainWindow);
        action_Open->setObjectName(QStringLiteral("action_Open"));
        action_Open->setEnabled(true);
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/new/prefix1/ico/folder.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Open->setIcon(icon4);
        action_Quit = new QAction(MainWindow);
        action_Quit->setObjectName(QStringLiteral("action_Quit"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/new/prefix1/ico/cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Quit->setIcon(icon5);
        action_imgset = new QAction(MainWindow);
        action_imgset->setObjectName(QStringLiteral("action_imgset"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/new/prefix1/ico/user.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_imgset->setIcon(icon6);
        action_start = new QAction(MainWindow);
        action_start->setObjectName(QStringLiteral("action_start"));
        action_start->setChecked(false);
        action_start->setEnabled(false);
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/new/prefix1/ico/video_play.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon7.addFile(QStringLiteral(":/new/prefix1/ico/minimize.png"), QSize(), QIcon::Normal, QIcon::On);
        action_start->setIcon(icon7);
        action_big = new QAction(MainWindow);
        action_big->setObjectName(QStringLiteral("action_big"));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/new/prefix1/ico/add.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_big->setIcon(icon8);
        action_small = new QAction(MainWindow);
        action_small->setObjectName(QStringLiteral("action_small"));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/new/prefix1/ico/minimize.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_small->setIcon(icon9);
        action_EXCEL_T = new QAction(MainWindow);
        action_EXCEL_T->setObjectName(QStringLiteral("action_EXCEL_T"));
        action_EXCEL_T->setIcon(icon2);
        action = new QAction(MainWindow);
        action->setObjectName(QStringLiteral("action"));
        action_pointAnalyze = new QAction(MainWindow);
        action_pointAnalyze->setObjectName(QStringLiteral("action_pointAnalyze"));
        actionReset = new QAction(MainWindow);
        actionReset->setObjectName(QStringLiteral("actionReset"));
        actionTest = new QAction(MainWindow);
        actionTest->setObjectName(QStringLiteral("actionTest"));
        action_init = new QAction(MainWindow);
        action_init->setObjectName(QStringLiteral("action_init"));
        actionCallback = new QAction(MainWindow);
        actionCallback->setObjectName(QStringLiteral("actionCallback"));
        actionSubHeight = new QAction(MainWindow);
        actionSubHeight->setObjectName(QStringLiteral("actionSubHeight"));
        action_2 = new QAction(MainWindow);
        action_2->setObjectName(QStringLiteral("action_2"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        groupBox_4 = new QGroupBox(centralWidget);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(530, 10, 541, 601));
        groupBox_4->setStyleSheet(QStringLiteral(""));
        startButton = new QPushButton(groupBox_4);
        startButton->setObjectName(QStringLiteral("startButton"));
        startButton->setEnabled(false);
        startButton->setGeometry(QRect(120, 10, 121, 31));
        startButton->setStyleSheet(QString::fromUtf8("font: 75 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/new/prefix1/ico/video_play.png"), QSize(), QIcon::Normal, QIcon::Off);
        startButton->setIcon(icon10);
        startButton->setCheckable(false);
        startButton->setChecked(false);
        startButton->setFlat(false);
        settings = new QPushButton(groupBox_4);
        settings->setObjectName(QStringLiteral("settings"));
        settings->setGeometry(QRect(250, 10, 121, 29));
        settings->setStyleSheet(QString::fromUtf8("font: 75 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        launchDevice = new QPushButton(groupBox_4);
        launchDevice->setObjectName(QStringLiteral("launchDevice"));
        launchDevice->setGeometry(QRect(10, 10, 101, 31));
        launchDevice->setStyleSheet(QString::fromUtf8("font: 75 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        groupBox_2 = new QGroupBox(groupBox_4);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 370, 521, 224));
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        toExcel = new QPushButton(groupBox_2);
        toExcel->setObjectName(QStringLiteral("toExcel"));

        gridLayout_3->addWidget(toExcel, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 0, 0, 1, 1);

        tableWidget = new QTableWidget(groupBox_2);
        if (tableWidget->columnCount() < 8)
            tableWidget->setColumnCount(8);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setSelectionMode(QAbstractItemView::MultiSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget->setSortingEnabled(true);
        tableWidget->horizontalHeader()->setCascadingSectionResizes(false);
        tableWidget->horizontalHeader()->setDefaultSectionSize(70);

        gridLayout_3->addWidget(tableWidget, 1, 0, 1, 2);

        groupBox_3 = new QGroupBox(groupBox_4);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 50, 511, 311));
        groupBox_5 = new QGroupBox(groupBox_3);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(330, 20, 161, 281));
        gridLayout_4 = new QGridLayout(groupBox_5);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        roiDraw = new QPushButton(groupBox_5);
        roiDraw->setObjectName(QStringLiteral("roiDraw"));

        gridLayout_4->addWidget(roiDraw, 2, 0, 1, 1);

        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        label_2 = new QLabel(groupBox_5);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_2);

        roiName = new QLineEdit(groupBox_5);
        roiName->setObjectName(QStringLiteral("roiName"));

        formLayout->setWidget(0, QFormLayout::FieldRole, roiName);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(1, QFormLayout::LabelRole, verticalSpacer_2);

        label_6 = new QLabel(groupBox_5);
        label_6->setObjectName(QStringLiteral("label_6"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_6);

        func = new QComboBox(groupBox_5);
        func->setObjectName(QStringLiteral("func"));

        formLayout->setWidget(2, QFormLayout::FieldRole, func);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(3, QFormLayout::LabelRole, verticalSpacer_4);

        label_4 = new QLabel(groupBox_5);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_4);

        team = new QComboBox(groupBox_5);
        team->setObjectName(QStringLiteral("team"));
        team->setLayoutDirection(Qt::LeftToRight);

        formLayout->setWidget(4, QFormLayout::FieldRole, team);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(5, QFormLayout::LabelRole, verticalSpacer_3);

        label = new QLabel(groupBox_5);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(6, QFormLayout::LabelRole, label);

        limitValue = new QLineEdit(groupBox_5);
        limitValue->setObjectName(QStringLiteral("limitValue"));

        formLayout->setWidget(6, QFormLayout::FieldRole, limitValue);

        label_3 = new QLabel(groupBox_5);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(8, QFormLayout::LabelRole, label_3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(7, QFormLayout::LabelRole, verticalSpacer);

        roiColor = new QPushButton(groupBox_5);
        roiColor->setObjectName(QStringLiteral("roiColor"));
        roiColor->setAutoFillBackground(false);
        roiColor->setStyleSheet(QStringLiteral("background-color: rgb(255, 0, 0);"));

        formLayout->setWidget(8, QFormLayout::FieldRole, roiColor);


        gridLayout_4->addLayout(formLayout, 1, 0, 1, 1);

        groupBox = new QGroupBox(groupBox_3);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 20, 301, 281));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        roiList = new QTableWidget(groupBox);
        if (roiList->columnCount() < 4)
            roiList->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        roiList->setHorizontalHeaderItem(0, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        roiList->setHorizontalHeaderItem(1, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        roiList->setHorizontalHeaderItem(2, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        roiList->setHorizontalHeaderItem(3, __qtablewidgetitem11);
        roiList->setObjectName(QStringLiteral("roiList"));
        roiList->setSelectionBehavior(QAbstractItemView::SelectRows);
        roiList->horizontalHeader()->setDefaultSectionSize(65);

        gridLayout_2->addWidget(roiList, 0, 0, 1, 1);

        view_box = new QGroupBox(centralWidget);
        view_box->setObjectName(QStringLiteral("view_box"));
        view_box->setGeometry(QRect(10, 30, 511, 511));
        sizePolicy.setHeightForWidth(view_box->sizePolicy().hasHeightForWidth());
        view_box->setSizePolicy(sizePolicy);
        view_box->setMouseTracking(false);
        view_box->setAutoFillBackground(false);
        view_box->setStyleSheet(QLatin1String("QGroupBox#view_box{\n"
"background-color: rgb(255, 255, 255);\n"
"border:2px;\n"
"border-radius:25px\n"
"}"));
        progressBar = new QProgressBar(view_box);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(0, 490, 501, 20));
        progressBar->setStyleSheet(QLatin1String("border:2px;\n"
"border-radius:25px"));
        progressBar->setValue(0);
        progressBar->setAlignment(Qt::AlignCenter);
        progressBar->setInvertedAppearance(false);
        progressBar->setTextDirection(QProgressBar::TopToBottom);
        base = new QStackedWidget(view_box);
        base->setObjectName(QStringLiteral("base"));
        base->setGeometry(QRect(10, 30, 491, 461));
        base->setAutoFillBackground(true);
        base->setStyleSheet(QStringLiteral(""));
        base->setMidLineWidth(0);
        threeDView = new QWidget();
        threeDView->setObjectName(QStringLiteral("threeDView"));
        base->addWidget(threeDView);
        realTimeView = new QWidget();
        realTimeView->setObjectName(QStringLiteral("realTimeView"));
        gridLayout = new QGridLayout(realTimeView);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        videoFrame = new QLabel(realTimeView);
        videoFrame->setObjectName(QStringLiteral("videoFrame"));
        videoFrame->setAutoFillBackground(true);

        gridLayout->addWidget(videoFrame, 0, 0, 1, 1);

        base->addWidget(realTimeView);
        singleFrameView = new QWidget();
        singleFrameView->setObjectName(QStringLiteral("singleFrameView"));
        base->addWidget(singleFrameView);
        twoDView = new QWidget();
        twoDView->setObjectName(QStringLiteral("twoDView"));
        base->addWidget(twoDView);
        layoutWidget = new QWidget(view_box);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 0, 481, 26));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        imgLeft = new QPushButton(layoutWidget);
        imgLeft->setObjectName(QStringLiteral("imgLeft"));
        imgLeft->setAutoFillBackground(false);
        imgLeft->setStyleSheet(QStringLiteral(""));
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/file/icons/ic_back.png"), QSize(), QIcon::Normal, QIcon::Off);
        imgLeft->setIcon(icon11);
        imgLeft->setAutoRepeat(false);
        imgLeft->setFlat(true);

        horizontalLayout->addWidget(imgLeft);

        imgRight = new QPushButton(layoutWidget);
        imgRight->setObjectName(QStringLiteral("imgRight"));
        imgRight->setAutoFillBackground(false);
        imgRight->setStyleSheet(QStringLiteral("color: rgb(255, 255, 127);"));
        QIcon icon12;
        icon12.addFile(QStringLiteral(":/file/icons/ic_forward.png"), QSize(), QIcon::Normal, QIcon::Off);
        imgRight->setIcon(icon12);
        imgRight->setFlat(true);

        horizontalLayout->addWidget(imgRight);

        imgUp = new QPushButton(layoutWidget);
        imgUp->setObjectName(QStringLiteral("imgUp"));
        QIcon icon13;
        icon13.addFile(QStringLiteral(":/icons/ic_up.png"), QSize(), QIcon::Normal, QIcon::Off);
        imgUp->setIcon(icon13);
        imgUp->setFlat(true);

        horizontalLayout->addWidget(imgUp);

        imgDown = new QPushButton(layoutWidget);
        imgDown->setObjectName(QStringLiteral("imgDown"));
        QIcon icon14;
        icon14.addFile(QStringLiteral(":/icons/ic_down.png"), QSize(), QIcon::Normal, QIcon::Off);
        imgDown->setIcon(icon14);
        imgDown->setFlat(true);

        horizontalLayout->addWidget(imgDown);

        imgBig = new QPushButton(layoutWidget);
        imgBig->setObjectName(QStringLiteral("imgBig"));
        QIcon icon15;
        icon15.addFile(QStringLiteral(":/file/icons/ic_zoom_in.png"), QSize(), QIcon::Normal, QIcon::Off);
        imgBig->setIcon(icon15);
        imgBig->setFlat(true);

        horizontalLayout->addWidget(imgBig);

        imgSmall = new QPushButton(layoutWidget);
        imgSmall->setObjectName(QStringLiteral("imgSmall"));
        QIcon icon16;
        icon16.addFile(QStringLiteral(":/file/icons/ic_zoom_out.png"), QSize(), QIcon::Normal, QIcon::Off);
        imgSmall->setIcon(icon16);
        imgSmall->setFlat(true);

        horizontalLayout->addWidget(imgSmall);

        imgRotate = new QPushButton(layoutWidget);
        imgRotate->setObjectName(QStringLiteral("imgRotate"));
        QIcon icon17;
        icon17.addFile(QStringLiteral(":/file/icons/ic_undo.png"), QSize(), QIcon::Normal, QIcon::Off);
        imgRotate->setIcon(icon17);
        imgRotate->setFlat(true);

        horizontalLayout->addWidget(imgRotate);

        twoDButton = new QPushButton(centralWidget);
        twoDButton->setObjectName(QStringLiteral("twoDButton"));
        twoDButton->setGeometry(QRect(10, 0, 75, 23));
        threeDButton = new QPushButton(centralWidget);
        threeDButton->setObjectName(QStringLiteral("threeDButton"));
        threeDButton->setGeometry(QRect(90, 0, 75, 23));
        realTimeButton = new QPushButton(centralWidget);
        realTimeButton->setObjectName(QStringLiteral("realTimeButton"));
        realTimeButton->setGeometry(QRect(170, 0, 75, 23));
        singleFrameButton = new QPushButton(centralWidget);
        singleFrameButton->setObjectName(QStringLiteral("singleFrameButton"));
        singleFrameButton->setGeometry(QRect(250, 0, 75, 23));
        rate = new QLabel(centralWidget);
        rate->setObjectName(QStringLiteral("rate"));
        rate->setGeometry(QRect(410, 10, 54, 12));
        pos = new QLabel(centralWidget);
        pos->setObjectName(QStringLiteral("pos"));
        pos->setGeometry(QRect(470, 10, 54, 12));
        comboBox = new QComboBox(centralWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(330, 0, 69, 22));
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 550, 511, 71));
        imgList = new QHBoxLayout(horizontalLayoutWidget);
        imgList->setSpacing(6);
        imgList->setContentsMargins(11, 11, 11, 11);
        imgList->setObjectName(QStringLiteral("imgList"));
        imgList->setContentsMargins(0, 0, 0, 0);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1071, 23));
        menu_S = new QMenu(menuBar);
        menu_S->setObjectName(QStringLiteral("menu_S"));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QStringLiteral("menu_2"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        statusBar->setEnabled(true);
        MainWindow->setStatusBar(statusBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        toolBar->setStyleSheet(QStringLiteral(""));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menuBar->addAction(menu_2->menuAction());
        menuBar->addAction(menu_S->menuAction());
        menuBar->addAction(menu->menuAction());
        menu_S->addAction(action_Net_Param);
        menu_S->addSeparator();
        menu_S->addSeparator();
        menu->addAction(action_about);
        menu_2->addAction(action_Open);
        menu_2->addAction(action_init);
        menu_2->addAction(action_start);
        menu_2->addAction(action);
        menu_2->addAction(action_pointAnalyze);
        menu_2->addAction(actionReset);
        menu_2->addAction(actionTest);
        menu_2->addAction(actionCallback);
        toolBar->addAction(action_Open);
        toolBar->addAction(action_start);
        toolBar->addAction(action_Quit);

        retranslateUi(MainWindow);
        QObject::connect(startButton, SIGNAL(clicked()), action_start, SLOT(trigger()));

        base->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "ScanControl", 0));
        action_Net_Param->setText(QApplication::translate("MainWindow", "\347\263\273\347\273\237\350\256\276\347\275\256", 0));
        action_about->setText(QApplication::translate("MainWindow", "\345\205\263\344\272\216", 0));
        action_CameraLight_Param->setText(QApplication::translate("MainWindow", "\347\233\270\346\234\272\345\222\214\345\205\211\346\272\220\345\217\202\346\225\260", 0));
        action_Connection->setText(QApplication::translate("MainWindow", "\350\277\236\346\216\245(&L)", 0));
#ifndef QT_NO_TOOLTIP
        action_Connection->setToolTip(QApplication::translate("MainWindow", "\350\277\236\346\216\245\347\275\221\347\273\234", 0));
#endif // QT_NO_TOOLTIP
        action_Open->setText(QApplication::translate("MainWindow", "\345\212\240\350\275\275\346\226\207\344\273\266(&O)", 0));
#ifndef QT_NO_TOOLTIP
        action_Open->setToolTip(QApplication::translate("MainWindow", "\345\212\240\350\275\275", 0));
#endif // QT_NO_TOOLTIP
        action_Quit->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272(&E)", 0));
#ifndef QT_NO_TOOLTIP
        action_Quit->setToolTip(QApplication::translate("MainWindow", "\351\200\200\345\207\272", 0));
#endif // QT_NO_TOOLTIP
        action_imgset->setText(QApplication::translate("MainWindow", "\345\233\276\345\203\217\346\243\200\346\265\213\345\217\202\346\225\260", 0));
        action_start->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213\346\265\213\351\207\217(&F3)", 0));
#ifndef QT_NO_TOOLTIP
        action_start->setToolTip(QApplication::translate("MainWindow", "\345\274\200\345\247\213\346\265\213\351\207\217/\345\201\234\346\255\242\346\265\213\351\207\217", 0));
#endif // QT_NO_TOOLTIP
        action_start->setShortcut(QApplication::translate("MainWindow", "F3", 0));
        action_big->setText(QApplication::translate("MainWindow", "\346\224\276\345\244\247(&B)", 0));
        action_small->setText(QApplication::translate("MainWindow", "\347\274\251\345\260\217(&S)", 0));
        action_EXCEL_T->setText(QApplication::translate("MainWindow", "\345\257\274\345\207\272EXCEL(T)", 0));
        action->setText(QApplication::translate("MainWindow", "\347\275\221\347\273\234\346\265\213\350\257\225", 0));
        action_pointAnalyze->setText(QApplication::translate("MainWindow", "\347\202\271\344\272\221\345\210\206\346\236\220", 0));
        actionReset->setText(QApplication::translate("MainWindow", "reset", 0));
        actionTest->setText(QApplication::translate("MainWindow", "test", 0));
        action_init->setText(QApplication::translate("MainWindow", "\345\220\257\345\212\250\346\277\200\345\205\211(&F2)", 0));
        action_init->setShortcut(QApplication::translate("MainWindow", "F2", 0));
        actionCallback->setText(QApplication::translate("MainWindow", "\345\206\205\351\203\250\350\247\246\345\217\221\351\207\207\351\233\206", 0));
        actionSubHeight->setText(QApplication::translate("MainWindow", "\346\265\213\351\207\217\351\253\230\345\267\256", 0));
        action_2->setText(QApplication::translate("MainWindow", "\346\265\213\351\207\217\351\253\230\345\267\256", 0));
        groupBox_4->setTitle(QString());
        startButton->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213\346\265\213\351\207\217", 0));
        settings->setText(QApplication::translate("MainWindow", "\345\217\202\346\225\260\350\256\276\347\275\256", 0));
        launchDevice->setText(QApplication::translate("MainWindow", "\345\220\257\345\212\250\346\277\200\345\205\211", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "\346\265\213\351\207\217\347\273\223\346\236\234", 0));
        toExcel->setText(QApplication::translate("MainWindow", "\345\257\274\345\207\272\347\273\223\346\236\234", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "ok/ng", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "\347\256\227\346\263\225", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "\345\214\272\345\237\237\345\220\215", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "\350\256\241\347\256\227\347\273\223\346\236\234", 0));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "\345\210\206\347\273\204", 0));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("MainWindow", "\346\234\200\345\260\217\345\200\274", 0));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("MainWindow", "\346\234\200\345\244\247\345\200\274", 0));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QApplication::translate("MainWindow", "\344\275\215\347\275\256", 0));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "\347\274\226\350\276\221\346\265\213\351\207\217\345\214\272\345\237\237", 0));
        groupBox_5->setTitle(QApplication::translate("MainWindow", "\347\273\230\345\210\266\345\214\272\345\237\237", 0));
        roiDraw->setText(QApplication::translate("MainWindow", "\347\273\230\345\210\266", 0));
        label_2->setText(QApplication::translate("MainWindow", "\345\214\272\345\237\237\345\220\215:", 0));
        label_6->setText(QApplication::translate("MainWindow", "\350\256\241\347\256\227:", 0));
        func->clear();
        func->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "\351\253\230\345\267\256", 0)
         << QApplication::translate("MainWindow", "\345\271\263\351\235\242\345\272\246", 0)
        );
        label_4->setText(QApplication::translate("MainWindow", "\345\214\272\345\237\237\345\210\206\347\273\204:", 0));
        team->clear();
        team->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "\345\210\206\347\273\2041", 0)
         << QApplication::translate("MainWindow", "\345\210\206\347\273\2042", 0)
         << QApplication::translate("MainWindow", "\345\210\206\347\273\2043", 0)
         << QApplication::translate("MainWindow", "\345\210\206\347\273\2044", 0)
         << QApplication::translate("MainWindow", "\345\210\206\347\273\2045", 0)
         << QApplication::translate("MainWindow", "\345\210\206\347\273\2046", 0)
         << QApplication::translate("MainWindow", "\345\210\206\347\273\2047", 0)
         << QApplication::translate("MainWindow", "\345\210\206\347\273\2048", 0)
         << QApplication::translate("MainWindow", "\345\210\206\347\273\2049", 0)
        );
        label->setText(QApplication::translate("MainWindow", "\346\265\213\351\207\217\351\230\210\345\200\274:", 0));
        limitValue->setText(QApplication::translate("MainWindow", "3", 0));
        label_3->setText(QApplication::translate("MainWindow", "\351\242\234\350\211\262:", 0));
        roiColor->setText(QString());
        groupBox->setTitle(QApplication::translate("MainWindow", "\345\214\272\345\237\237\345\210\227\350\241\250", 0));
        QTableWidgetItem *___qtablewidgetitem8 = roiList->horizontalHeaderItem(0);
        ___qtablewidgetitem8->setText(QApplication::translate("MainWindow", "\345\214\272\345\237\237\345\220\215", 0));
        QTableWidgetItem *___qtablewidgetitem9 = roiList->horizontalHeaderItem(1);
        ___qtablewidgetitem9->setText(QApplication::translate("MainWindow", "\345\210\206\347\273\204", 0));
        QTableWidgetItem *___qtablewidgetitem10 = roiList->horizontalHeaderItem(2);
        ___qtablewidgetitem10->setText(QApplication::translate("MainWindow", "\347\256\227\346\263\225", 0));
        QTableWidgetItem *___qtablewidgetitem11 = roiList->horizontalHeaderItem(3);
        ___qtablewidgetitem11->setText(QApplication::translate("MainWindow", "\351\230\210\345\200\274", 0));
        view_box->setTitle(QString());
        progressBar->setFormat(QApplication::translate("MainWindow", "%p%", 0));
        videoFrame->setText(QString());
#ifndef QT_NO_TOOLTIP
        imgLeft->setToolTip(QApplication::translate("MainWindow", "\345\267\246\347\247\273", 0));
#endif // QT_NO_TOOLTIP
        imgLeft->setText(QString());
#ifndef QT_NO_TOOLTIP
        imgRight->setToolTip(QApplication::translate("MainWindow", "\345\217\263\347\247\273", 0));
#endif // QT_NO_TOOLTIP
        imgRight->setText(QString());
#ifndef QT_NO_TOOLTIP
        imgUp->setToolTip(QApplication::translate("MainWindow", "\344\270\212\347\247\273", 0));
#endif // QT_NO_TOOLTIP
        imgUp->setText(QString());
#ifndef QT_NO_TOOLTIP
        imgDown->setToolTip(QApplication::translate("MainWindow", "\344\270\213\347\247\273", 0));
#endif // QT_NO_TOOLTIP
        imgDown->setText(QString());
#ifndef QT_NO_TOOLTIP
        imgBig->setToolTip(QApplication::translate("MainWindow", "\346\224\276\345\244\247", 0));
#endif // QT_NO_TOOLTIP
        imgBig->setText(QString());
#ifndef QT_NO_TOOLTIP
        imgSmall->setToolTip(QApplication::translate("MainWindow", "\347\274\251\345\260\217", 0));
#endif // QT_NO_TOOLTIP
        imgSmall->setText(QString());
#ifndef QT_NO_TOOLTIP
        imgRotate->setToolTip(QApplication::translate("MainWindow", "\346\227\213\350\275\254", 0));
#endif // QT_NO_TOOLTIP
        imgRotate->setText(QString());
        twoDButton->setText(QApplication::translate("MainWindow", "2D\346\230\276\347\244\272", 0));
        threeDButton->setText(QApplication::translate("MainWindow", "3D\346\230\276\347\244\272", 0));
        realTimeButton->setText(QApplication::translate("MainWindow", "\345\256\236\346\227\266\346\230\276\347\244\272", 0));
        singleFrameButton->setText(QApplication::translate("MainWindow", "\345\215\225\345\270\247\346\230\276\347\244\272", 0));
        rate->setText(QApplication::translate("MainWindow", "0", 0));
        pos->setText(QApplication::translate("MainWindow", "0,0", 0));
        menu_S->setTitle(QApplication::translate("MainWindow", "\350\256\276\347\275\256(&S)", 0));
        menu->setTitle(QApplication::translate("MainWindow", "\345\270\256\345\212\251(&H)", 0));
        menu_2->setTitle(QApplication::translate("MainWindow", "\344\273\273\345\212\241(&N)", 0));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
