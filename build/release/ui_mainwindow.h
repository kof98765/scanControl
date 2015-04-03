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
#include <QtWidgets/QTabWidget>
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
    QAction *actionTest;
    QAction *actionReset;
    QAction *actionCal;
    QAction *action_init;
    QAction *actionCallback;
    QAction *actionSubHeight;
    QAction *action_2;
    QAction *actionStop;
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
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QTableWidget *roiList;
    QTabWidget *team2;
    QWidget *tab_2;
    QWidget *layoutWidget_2;
    QFormLayout *formLayout;
    QLabel *label_2;
    QLineEdit *roiName;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_6;
    QComboBox *func;
    QSpacerItem *verticalSpacer_3;
    QLabel *label;
    QLineEdit *limitValue;
    QSpacerItem *verticalSpacer;
    QLabel *label_3;
    QPushButton *roiColor;
    QLabel *label_4;
    QComboBox *team;
    QPushButton *roiDraw;
    QWidget *tab;
    QPushButton *pushButton_2;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout_2;
    QLabel *Label;
    QLineEdit *roiname2;
    QLabel *Label_2;
    QComboBox *ComboBox;
    QLabel *Label_3;
    QComboBox *func2;
    QLabel *Label_4;
    QLineEdit *roiSize;
    QLabel *Label_5;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *pointX;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *pointY;
    QLabel *Label_6;
    QComboBox *unit;
    QLabel *Label_7;
    QLineEdit *minValue;
    QLabel *Label_8;
    QLineEdit *maxValue;
    QLabel *Label_9;
    QPushButton *roiColor2;
    QLabel *connect;
    QPushButton *reset;
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
        MainWindow->resize(1280, 698);
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
        actionTest = new QAction(MainWindow);
        actionTest->setObjectName(QStringLiteral("actionTest"));
        actionReset = new QAction(MainWindow);
        actionReset->setObjectName(QStringLiteral("actionReset"));
        actionCal = new QAction(MainWindow);
        actionCal->setObjectName(QStringLiteral("actionCal"));
        action_init = new QAction(MainWindow);
        action_init->setObjectName(QStringLiteral("action_init"));
        actionCallback = new QAction(MainWindow);
        actionCallback->setObjectName(QStringLiteral("actionCallback"));
        actionSubHeight = new QAction(MainWindow);
        actionSubHeight->setObjectName(QStringLiteral("actionSubHeight"));
        action_2 = new QAction(MainWindow);
        action_2->setObjectName(QStringLiteral("action_2"));
        actionStop = new QAction(MainWindow);
        actionStop->setObjectName(QStringLiteral("actionStop"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        groupBox_4 = new QGroupBox(centralWidget);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(530, 10, 731, 601));
        groupBox_4->setStyleSheet(QStringLiteral(""));
        startButton = new QPushButton(groupBox_4);
        startButton->setObjectName(QStringLiteral("startButton"));
        startButton->setEnabled(true);
        startButton->setGeometry(QRect(120, 10, 101, 31));
        startButton->setStyleSheet(QString::fromUtf8("font: 75 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/new/prefix1/ico/video_play.png"), QSize(), QIcon::Normal, QIcon::Off);
        startButton->setIcon(icon10);
        startButton->setCheckable(false);
        startButton->setChecked(false);
        startButton->setFlat(false);
        settings = new QPushButton(groupBox_4);
        settings->setObjectName(QStringLiteral("settings"));
        settings->setGeometry(QRect(230, 10, 101, 31));
        settings->setStyleSheet(QString::fromUtf8("font: 75 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        launchDevice = new QPushButton(groupBox_4);
        launchDevice->setObjectName(QStringLiteral("launchDevice"));
        launchDevice->setGeometry(QRect(10, 10, 101, 31));
        launchDevice->setStyleSheet(QString::fromUtf8("font: 75 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        groupBox_2 = new QGroupBox(groupBox_4);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 370, 621, 224));
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
        if (tableWidget->columnCount() < 6)
            tableWidget->setColumnCount(6);
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
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setSelectionMode(QAbstractItemView::MultiSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget->setSortingEnabled(true);
        tableWidget->horizontalHeader()->setCascadingSectionResizes(false);
        tableWidget->horizontalHeader()->setDefaultSectionSize(70);

        gridLayout_3->addWidget(tableWidget, 1, 0, 1, 2);

        groupBox_3 = new QGroupBox(groupBox_4);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 50, 621, 311));
        groupBox = new QGroupBox(groupBox_3);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 20, 281, 281));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        roiList = new QTableWidget(groupBox);
        if (roiList->columnCount() < 4)
            roiList->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        roiList->setHorizontalHeaderItem(0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        roiList->setHorizontalHeaderItem(1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        roiList->setHorizontalHeaderItem(2, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        roiList->setHorizontalHeaderItem(3, __qtablewidgetitem9);
        roiList->setObjectName(QStringLiteral("roiList"));
        roiList->setSelectionBehavior(QAbstractItemView::SelectRows);
        roiList->horizontalHeader()->setDefaultSectionSize(65);

        gridLayout_2->addWidget(roiList, 0, 0, 1, 1);

        team2 = new QTabWidget(groupBox_3);
        team2->setObjectName(QStringLiteral("team2"));
        team2->setGeometry(QRect(310, 10, 301, 291));
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        layoutWidget_2 = new QWidget(tab_2);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(0, 0, 151, 231));
        formLayout = new QFormLayout(layoutWidget_2);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_2);

        roiName = new QLineEdit(layoutWidget_2);
        roiName->setObjectName(QStringLiteral("roiName"));

        formLayout->setWidget(0, QFormLayout::FieldRole, roiName);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(2, QFormLayout::LabelRole, verticalSpacer_2);

        label_6 = new QLabel(layoutWidget_2);
        label_6->setObjectName(QStringLiteral("label_6"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_6);

        func = new QComboBox(layoutWidget_2);
        func->setObjectName(QStringLiteral("func"));

        formLayout->setWidget(3, QFormLayout::FieldRole, func);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(4, QFormLayout::LabelRole, verticalSpacer_3);

        label = new QLabel(layoutWidget_2);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label);

        limitValue = new QLineEdit(layoutWidget_2);
        limitValue->setObjectName(QStringLiteral("limitValue"));

        formLayout->setWidget(5, QFormLayout::FieldRole, limitValue);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(6, QFormLayout::LabelRole, verticalSpacer);

        label_3 = new QLabel(layoutWidget_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(7, QFormLayout::LabelRole, label_3);

        roiColor = new QPushButton(layoutWidget_2);
        roiColor->setObjectName(QStringLiteral("roiColor"));
        roiColor->setAutoFillBackground(false);
        roiColor->setStyleSheet(QStringLiteral("background-color: rgb(255, 0, 0);"));

        formLayout->setWidget(7, QFormLayout::FieldRole, roiColor);

        label_4 = new QLabel(layoutWidget_2);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_4);

        team = new QComboBox(layoutWidget_2);
        team->setObjectName(QStringLiteral("team"));

        formLayout->setWidget(1, QFormLayout::FieldRole, team);

        roiDraw = new QPushButton(tab_2);
        roiDraw->setObjectName(QStringLiteral("roiDraw"));
        roiDraw->setGeometry(QRect(0, 240, 151, 23));
        team2->addTab(tab_2, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        pushButton_2 = new QPushButton(tab);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(0, 240, 151, 23));
        formLayoutWidget = new QWidget(tab);
        formLayoutWidget->setObjectName(QStringLiteral("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(0, 0, 154, 235));
        formLayout_2 = new QFormLayout(formLayoutWidget);
        formLayout_2->setSpacing(6);
        formLayout_2->setContentsMargins(11, 11, 11, 11);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        formLayout_2->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout_2->setContentsMargins(0, 0, 0, 0);
        Label = new QLabel(formLayoutWidget);
        Label->setObjectName(QStringLiteral("Label"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, Label);

        roiname2 = new QLineEdit(formLayoutWidget);
        roiname2->setObjectName(QStringLiteral("roiname2"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, roiname2);

        Label_2 = new QLabel(formLayoutWidget);
        Label_2->setObjectName(QStringLiteral("Label_2"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, Label_2);

        ComboBox = new QComboBox(formLayoutWidget);
        ComboBox->setObjectName(QStringLiteral("ComboBox"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, ComboBox);

        Label_3 = new QLabel(formLayoutWidget);
        Label_3->setObjectName(QStringLiteral("Label_3"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, Label_3);

        func2 = new QComboBox(formLayoutWidget);
        func2->setObjectName(QStringLiteral("func2"));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, func2);

        Label_4 = new QLabel(formLayoutWidget);
        Label_4->setObjectName(QStringLiteral("Label_4"));

        formLayout_2->setWidget(3, QFormLayout::LabelRole, Label_4);

        roiSize = new QLineEdit(formLayoutWidget);
        roiSize->setObjectName(QStringLiteral("roiSize"));

        formLayout_2->setWidget(3, QFormLayout::FieldRole, roiSize);

        Label_5 = new QLabel(formLayoutWidget);
        Label_5->setObjectName(QStringLiteral("Label_5"));

        formLayout_2->setWidget(4, QFormLayout::LabelRole, Label_5);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        pointX = new QLineEdit(formLayoutWidget);
        pointX->setObjectName(QStringLiteral("pointX"));

        horizontalLayout_2->addWidget(pointX);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        pointY = new QLineEdit(formLayoutWidget);
        pointY->setObjectName(QStringLiteral("pointY"));

        horizontalLayout_2->addWidget(pointY);


        formLayout_2->setLayout(4, QFormLayout::FieldRole, horizontalLayout_2);

        Label_6 = new QLabel(formLayoutWidget);
        Label_6->setObjectName(QStringLiteral("Label_6"));

        formLayout_2->setWidget(5, QFormLayout::LabelRole, Label_6);

        unit = new QComboBox(formLayoutWidget);
        unit->setObjectName(QStringLiteral("unit"));

        formLayout_2->setWidget(5, QFormLayout::FieldRole, unit);

        Label_7 = new QLabel(formLayoutWidget);
        Label_7->setObjectName(QStringLiteral("Label_7"));

        formLayout_2->setWidget(6, QFormLayout::LabelRole, Label_7);

        minValue = new QLineEdit(formLayoutWidget);
        minValue->setObjectName(QStringLiteral("minValue"));

        formLayout_2->setWidget(6, QFormLayout::FieldRole, minValue);

        Label_8 = new QLabel(formLayoutWidget);
        Label_8->setObjectName(QStringLiteral("Label_8"));

        formLayout_2->setWidget(7, QFormLayout::LabelRole, Label_8);

        maxValue = new QLineEdit(formLayoutWidget);
        maxValue->setObjectName(QStringLiteral("maxValue"));

        formLayout_2->setWidget(7, QFormLayout::FieldRole, maxValue);

        Label_9 = new QLabel(formLayoutWidget);
        Label_9->setObjectName(QStringLiteral("Label_9"));

        formLayout_2->setWidget(8, QFormLayout::LabelRole, Label_9);

        roiColor2 = new QPushButton(formLayoutWidget);
        roiColor2->setObjectName(QStringLiteral("roiColor2"));

        formLayout_2->setWidget(8, QFormLayout::FieldRole, roiColor2);

        team2->addTab(tab, QString());
        connect = new QLabel(groupBox_4);
        connect->setObjectName(QStringLiteral("connect"));
        connect->setGeometry(QRect(440, 10, 101, 31));
        connect->setStyleSheet(QString::fromUtf8("font: 18pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
""));
        reset = new QPushButton(groupBox_4);
        reset->setObjectName(QStringLiteral("reset"));
        reset->setGeometry(QRect(340, 10, 75, 31));
        reset->setStyleSheet(QString::fromUtf8("font: 75 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
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
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 540, 511, 80));
        imgList = new QHBoxLayout(horizontalLayoutWidget);
        imgList->setSpacing(6);
        imgList->setContentsMargins(11, 11, 11, 11);
        imgList->setObjectName(QStringLiteral("imgList"));
        imgList->setContentsMargins(0, 0, 0, 0);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1280, 23));
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
        menu_2->addAction(actionTest);
        menu_2->addAction(actionReset);
        menu_2->addAction(actionCal);
        menu_2->addAction(actionCallback);
        menu_2->addAction(actionStop);
        toolBar->addAction(action_Open);
        toolBar->addAction(action_start);
        toolBar->addAction(action_Quit);
        toolBar->addAction(actionTest);
        toolBar->addAction(actionCal);

        retranslateUi(MainWindow);
        QObject::connect(startButton, SIGNAL(clicked()), action_start, SLOT(trigger()));

        team2->setCurrentIndex(0);
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
        actionTest->setText(QApplication::translate("MainWindow", "\345\220\210\346\210\220", 0));
#ifndef QT_NO_TOOLTIP
        actionTest->setToolTip(QApplication::translate("MainWindow", "\345\220\210\346\210\220", 0));
#endif // QT_NO_TOOLTIP
        actionReset->setText(QApplication::translate("MainWindow", "reset", 0));
        actionCal->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213\350\256\241\347\256\227", 0));
        action_init->setText(QApplication::translate("MainWindow", "\345\220\257\345\212\250\346\277\200\345\205\211(&F2)", 0));
        action_init->setShortcut(QApplication::translate("MainWindow", "F2", 0));
        actionCallback->setText(QApplication::translate("MainWindow", "\345\206\205\351\203\250\350\247\246\345\217\221\351\207\207\351\233\206", 0));
        actionSubHeight->setText(QApplication::translate("MainWindow", "\346\265\213\351\207\217\351\253\230\345\267\256", 0));
        action_2->setText(QApplication::translate("MainWindow", "\346\265\213\351\207\217\351\253\230\345\267\256", 0));
        actionStop->setText(QApplication::translate("MainWindow", "stop", 0));
        groupBox_4->setTitle(QString());
        startButton->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213\346\265\213\351\207\217", 0));
        settings->setText(QApplication::translate("MainWindow", "\345\217\202\346\225\260\350\256\276\347\275\256", 0));
        launchDevice->setText(QApplication::translate("MainWindow", "\345\220\257\345\212\250\346\277\200\345\205\211", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "\346\265\213\351\207\217\347\273\223\346\236\234", 0));
        toExcel->setText(QApplication::translate("MainWindow", "\345\257\274\345\207\272\347\273\223\346\236\234", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "ok/ng", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "\347\261\273\345\236\213", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "\345\210\206\347\273\204", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "\350\256\241\347\256\227\347\273\223\346\236\234", 0));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "\346\234\200\345\260\217\345\200\274", 0));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("MainWindow", "\346\234\200\345\244\247\345\200\274", 0));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "\347\274\226\350\276\221\346\265\213\351\207\217\345\214\272\345\237\237", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "\345\214\272\345\237\237\345\210\227\350\241\250", 0));
        QTableWidgetItem *___qtablewidgetitem6 = roiList->horizontalHeaderItem(0);
        ___qtablewidgetitem6->setText(QApplication::translate("MainWindow", "\345\214\272\345\237\237\345\220\215", 0));
        QTableWidgetItem *___qtablewidgetitem7 = roiList->horizontalHeaderItem(1);
        ___qtablewidgetitem7->setText(QApplication::translate("MainWindow", "\345\210\206\347\273\204", 0));
        QTableWidgetItem *___qtablewidgetitem8 = roiList->horizontalHeaderItem(2);
        ___qtablewidgetitem8->setText(QApplication::translate("MainWindow", "\347\261\273\345\236\213", 0));
        QTableWidgetItem *___qtablewidgetitem9 = roiList->horizontalHeaderItem(3);
        ___qtablewidgetitem9->setText(QApplication::translate("MainWindow", "\351\230\210\345\200\274", 0));
        label_2->setText(QApplication::translate("MainWindow", "\345\214\272\345\237\237\345\220\215:", 0));
        label_6->setText(QApplication::translate("MainWindow", "\347\261\273\345\236\213:", 0));
        func->clear();
        func->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "\345\256\232\344\275\215\345\214\272\345\237\237", 0)
         << QApplication::translate("MainWindow", "\346\220\234\347\264\242\345\214\272\345\237\237", 0)
         << QApplication::translate("MainWindow", "\350\256\241\347\256\227\345\271\263\351\235\242\345\272\246", 0)
         << QApplication::translate("MainWindow", "\350\256\241\347\256\227\351\253\230\345\267\256", 0)
        );
        label->setText(QApplication::translate("MainWindow", "\346\265\213\351\207\217\351\230\210\345\200\274:", 0));
        limitValue->setText(QApplication::translate("MainWindow", "3", 0));
        label_3->setText(QApplication::translate("MainWindow", "\351\242\234\350\211\262:", 0));
        roiColor->setText(QString());
        label_4->setText(QApplication::translate("MainWindow", "\345\210\206\347\273\204:", 0));
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
        );
        roiDraw->setText(QApplication::translate("MainWindow", "\347\273\230\345\210\266", 0));
        team2->setTabText(team2->indexOf(tab_2), QApplication::translate("MainWindow", "\347\273\230\345\210\266\345\214\272\345\237\237", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "\347\273\230\345\210\266", 0));
        Label->setText(QApplication::translate("MainWindow", "\345\214\272\345\237\237\345\220\215:", 0));
        Label_2->setText(QApplication::translate("MainWindow", "\345\210\206\347\273\204:", 0));
        Label_3->setText(QApplication::translate("MainWindow", "\347\261\273\345\236\213:", 0));
        Label_4->setText(QApplication::translate("MainWindow", "\345\214\272\345\237\237\345\244\247\345\260\217:", 0));
        Label_5->setText(QApplication::translate("MainWindow", "\345\235\220\346\240\207:", 0));
        Label_6->setText(QApplication::translate("MainWindow", "\345\215\225\344\275\215:", 0));
        unit->clear();
        unit->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "\345\276\256\347\261\263", 0)
         << QApplication::translate("MainWindow", "\346\257\253\347\261\263", 0)
        );
        Label_7->setText(QApplication::translate("MainWindow", "\346\234\200\345\260\217\345\200\274:", 0));
        Label_8->setText(QApplication::translate("MainWindow", "\346\234\200\345\244\247\345\200\274:", 0));
        Label_9->setText(QApplication::translate("MainWindow", "\351\242\234\350\211\262:", 0));
        roiColor2->setText(QString());
        team2->setTabText(team2->indexOf(tab), QApplication::translate("MainWindow", "\351\224\256\345\205\245\345\214\272\345\237\237", 0));
        connect->setText(QString());
        reset->setText(QApplication::translate("MainWindow", "\345\244\215\344\275\215", 0));
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
