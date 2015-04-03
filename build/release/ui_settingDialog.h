/********************************************************************************
** Form generated from reading UI file 'settingDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGDIALOG_H
#define UI_SETTINGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mySettings
{
public:
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_5;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *Button_Yes;
    QPushButton *pushButton_Cancel;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_6;
    QPushButton *open;
    QLineEdit *path;
    QLabel *label_2;
    QWidget *tab_2;
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_7;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *robotIp;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_4;
    QLineEdit *robotPort;
    QGridLayout *gridLayout_10;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *horizontalSpacer_6;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *cameraIp;
    QLineEdit *cameraPort;
    QLabel *label_19;
    QLineEdit *udpPort;
    QSpacerItem *horizontalSpacer_8;
    QSpacerItem *horizontalSpacer_9;
    QSpacerItem *horizontalSpacer_11;
    QSpacerItem *horizontalSpacer_10;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_11;
    QSpacerItem *horizontalSpacer_13;
    QLineEdit *sendData;
    QPushButton *sendButton;
    QTextEdit *recvData;
    QLabel *label_29;
    QHBoxLayout *horizontalLayout_7;
    QWidget *tab_3;
    QGridLayout *gridLayout_4;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_5;
    QLineEdit *erosion;
    QLabel *label_16;
    QLineEdit *grayDvalue;
    QLabel *label_39;
    QLineEdit *badMaxArea;
    QLineEdit *badMinHeight;
    QLabel *label_10;
    QLineEdit *badMinRadius;
    QSpinBox *imgNum;
    QLineEdit *badMaxWidth;
    QLabel *label_17;
    QLineEdit *minGray;
    QLineEdit *smothWidth;
    QLabel *label_9;
    QLineEdit *contrast;
    QLineEdit *checkMinArea;
    QLineEdit *badMinArea;
    QLabel *label_11;
    QLabel *label_6;
    QLineEdit *badMinWidth;
    QLineEdit *smothHeight;
    QLineEdit *checkMaxArea;
    QLabel *label_8;
    QLabel *label_15;
    QLineEdit *maxGray;
    QLabel *label_18;
    QLineEdit *badMaxradius;
    QLineEdit *badMaxHeight;
    QLabel *label_7;
    QCheckBox *doubleTurn;
    QSpacerItem *horizontalSpacer;
    QPushButton *default_2;
    QWidget *tab_4;
    QGridLayout *gridLayout_8;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_9;
    QCheckBox *cameraCheck;
    QLabel *label_12;
    QLabel *label_13;
    QLineEdit *cameraName;
    QLineEdit *cameraDevice;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_14;
    QSpinBox *camera_exposureTime;
    QWidget *tab_5;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *label_25;
    QComboBox *select_device;
    QLabel *label_21;
    QSpinBox *profileCount;
    QLabel *label_22;
    QComboBox *exposure;
    QLabel *label_24;
    QComboBox *resolution;
    QLabel *label_20;
    QComboBox *resampleValue;
    QLabel *label_27;
    QComboBox *median;
    QLabel *label_28;
    QComboBox *average;
    QLabel *label_30;
    QComboBox *trigger;
    QLabel *label_31;
    QComboBox *triggerMode;
    QLabel *label_32;
    QComboBox *triggerSource;
    QLabel *label_33;
    QComboBox *triggerPolarity;
    QLabel *label_35;
    QComboBox *voltage;
    QLabel *label_36;
    QComboBox *digitalInputs;
    QLabel *label_23;
    QHBoxLayout *horizontalLayout_3;
    QComboBox *autoThreshold;
    QSpinBox *threshold;
    QLabel *label_26;
    QSpinBox *rate;
    QTextBrowser *debug;
    QLabel *label_37;
    QPushButton *readSet;
    QPushButton *connecct;
    QDoubleSpinBox *testValue;
    QWidget *tab_6;
    QWidget *formLayoutWidget_2;
    QFormLayout *formLayout_2;
    QLabel *label_34;
    QHBoxLayout *horizontalLayout_6;
    QSpinBox *ip32;
    QSpinBox *ip24;
    QSpinBox *ip16;
    QSpinBox *ip0;
    QLabel *label_41;
    QSpinBox *dataPort;
    QLabel *label_40;
    QSpinBox *commandPort;
    QLabel *label_38;
    QSpinBox *freq;
    QRadioButton *usb;
    QRadioButton *Ethernet;

    void setupUi(QDialog *mySettings)
    {
        if (mySettings->objectName().isEmpty())
            mySettings->setObjectName(QStringLiteral("mySettings"));
        mySettings->resize(652, 620);
        groupBox = new QGroupBox(mySettings);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(9, 9, 631, 601));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));

        gridLayout->addLayout(horizontalLayout_5, 1, 1, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer_3 = new QSpacerItem(220, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        Button_Yes = new QPushButton(groupBox);
        Button_Yes->setObjectName(QStringLiteral("Button_Yes"));

        horizontalLayout_2->addWidget(Button_Yes);

        pushButton_Cancel = new QPushButton(groupBox);
        pushButton_Cancel->setObjectName(QStringLiteral("pushButton_Cancel"));

        horizontalLayout_2->addWidget(pushButton_Cancel);


        horizontalLayout_4->addLayout(horizontalLayout_2);


        gridLayout->addLayout(horizontalLayout_4, 1, 0, 1, 1);

        tabWidget = new QTabWidget(groupBox);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout_2 = new QGridLayout(tab);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        groupBox_3 = new QGroupBox(tab);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        gridLayout_6 = new QGridLayout(groupBox_3);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        open = new QPushButton(groupBox_3);
        open->setObjectName(QStringLiteral("open"));

        gridLayout_6->addWidget(open, 1, 2, 1, 1);

        path = new QLineEdit(groupBox_3);
        path->setObjectName(QStringLiteral("path"));

        gridLayout_6->addWidget(path, 1, 1, 1, 1);

        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_6->addWidget(label_2, 1, 0, 1, 1);


        gridLayout_2->addWidget(groupBox_3, 0, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        gridLayout_3 = new QGridLayout(tab_2);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        groupBox_4 = new QGroupBox(tab_2);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        gridLayout_7 = new QGridLayout(groupBox_4);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(groupBox_4);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        robotIp = new QLineEdit(groupBox_4);
        robotIp->setObjectName(QStringLiteral("robotIp"));

        horizontalLayout->addWidget(robotIp);

        horizontalSpacer_5 = new QSpacerItem(13, 13, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);

        label_3 = new QLabel(groupBox_4);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout->addWidget(label_3);

        horizontalSpacer_4 = new QSpacerItem(13, 13, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        robotPort = new QLineEdit(groupBox_4);
        robotPort->setObjectName(QStringLiteral("robotPort"));

        horizontalLayout->addWidget(robotPort);


        gridLayout_7->addLayout(horizontalLayout, 5, 0, 1, 6);

        gridLayout_10 = new QGridLayout();
        gridLayout_10->setObjectName(QStringLiteral("gridLayout_10"));
        horizontalSpacer_7 = new QSpacerItem(13, 13, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_10->addItem(horizontalSpacer_7, 0, 5, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(13, 13, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_10->addItem(horizontalSpacer_6, 0, 2, 1, 1);

        label_4 = new QLabel(groupBox_4);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_10->addWidget(label_4, 0, 0, 1, 1);

        label_5 = new QLabel(groupBox_4);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_10->addWidget(label_5, 0, 3, 1, 1);

        cameraIp = new QLineEdit(groupBox_4);
        cameraIp->setObjectName(QStringLiteral("cameraIp"));

        gridLayout_10->addWidget(cameraIp, 0, 1, 1, 1);

        cameraPort = new QLineEdit(groupBox_4);
        cameraPort->setObjectName(QStringLiteral("cameraPort"));

        gridLayout_10->addWidget(cameraPort, 0, 4, 1, 1);

        label_19 = new QLabel(groupBox_4);
        label_19->setObjectName(QStringLiteral("label_19"));

        gridLayout_10->addWidget(label_19, 1, 0, 1, 1);

        udpPort = new QLineEdit(groupBox_4);
        udpPort->setObjectName(QStringLiteral("udpPort"));

        gridLayout_10->addWidget(udpPort, 1, 1, 1, 1);


        gridLayout_7->addLayout(gridLayout_10, 1, 0, 1, 6);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_7->addItem(horizontalSpacer_8, 4, 5, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_7->addItem(horizontalSpacer_9, 4, 2, 1, 1);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_7->addItem(horizontalSpacer_11, 4, 3, 1, 1);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_7->addItem(horizontalSpacer_10, 4, 4, 1, 1);

        groupBox_6 = new QGroupBox(groupBox_4);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        gridLayout_11 = new QGridLayout(groupBox_6);
        gridLayout_11->setObjectName(QStringLiteral("gridLayout_11"));
        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_11->addItem(horizontalSpacer_13, 0, 2, 1, 1);

        sendData = new QLineEdit(groupBox_6);
        sendData->setObjectName(QStringLiteral("sendData"));

        gridLayout_11->addWidget(sendData, 0, 0, 1, 1);

        sendButton = new QPushButton(groupBox_6);
        sendButton->setObjectName(QStringLiteral("sendButton"));

        gridLayout_11->addWidget(sendButton, 0, 1, 1, 1);

        recvData = new QTextEdit(groupBox_6);
        recvData->setObjectName(QStringLiteral("recvData"));

        gridLayout_11->addWidget(recvData, 2, 0, 1, 1);

        label_29 = new QLabel(groupBox_6);
        label_29->setObjectName(QStringLiteral("label_29"));

        gridLayout_11->addWidget(label_29, 1, 0, 1, 1);


        gridLayout_7->addWidget(groupBox_6, 2, 0, 2, 6);


        gridLayout_3->addWidget(groupBox_4, 0, 0, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));

        gridLayout_3->addLayout(horizontalLayout_7, 0, 1, 1, 1);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        gridLayout_4 = new QGridLayout(tab_3);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        groupBox_2 = new QGroupBox(tab_3);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_5 = new QGridLayout(groupBox_2);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        erosion = new QLineEdit(groupBox_2);
        erosion->setObjectName(QStringLiteral("erosion"));
        erosion->setInputMethodHints(Qt::ImhDigitsOnly);

        gridLayout_5->addWidget(erosion, 13, 2, 1, 1);

        label_16 = new QLabel(groupBox_2);
        label_16->setObjectName(QStringLiteral("label_16"));

        gridLayout_5->addWidget(label_16, 4, 0, 1, 1);

        grayDvalue = new QLineEdit(groupBox_2);
        grayDvalue->setObjectName(QStringLiteral("grayDvalue"));
        grayDvalue->setInputMethodHints(Qt::ImhDigitsOnly);

        gridLayout_5->addWidget(grayDvalue, 9, 2, 1, 1);

        label_39 = new QLabel(groupBox_2);
        label_39->setObjectName(QStringLiteral("label_39"));

        gridLayout_5->addWidget(label_39, 14, 0, 1, 1);

        badMaxArea = new QLineEdit(groupBox_2);
        badMaxArea->setObjectName(QStringLiteral("badMaxArea"));
        badMaxArea->setInputMethodHints(Qt::ImhDigitsOnly);

        gridLayout_5->addWidget(badMaxArea, 1, 4, 1, 1);

        badMinHeight = new QLineEdit(groupBox_2);
        badMinHeight->setObjectName(QStringLiteral("badMinHeight"));
        badMinHeight->setInputMethodHints(Qt::ImhDigitsOnly);

        gridLayout_5->addWidget(badMinHeight, 3, 2, 1, 1);

        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout_5->addWidget(label_10, 2, 0, 1, 1);

        badMinRadius = new QLineEdit(groupBox_2);
        badMinRadius->setObjectName(QStringLiteral("badMinRadius"));
        badMinRadius->setInputMethodHints(Qt::ImhDigitsOnly);

        gridLayout_5->addWidget(badMinRadius, 4, 2, 1, 1);

        imgNum = new QSpinBox(groupBox_2);
        imgNum->setObjectName(QStringLiteral("imgNum"));
        imgNum->setMinimum(1);
        imgNum->setMaximum(8);
        imgNum->setValue(8);

        gridLayout_5->addWidget(imgNum, 14, 2, 1, 1);

        badMaxWidth = new QLineEdit(groupBox_2);
        badMaxWidth->setObjectName(QStringLiteral("badMaxWidth"));
        badMaxWidth->setInputMethodHints(Qt::ImhDigitsOnly);

        gridLayout_5->addWidget(badMaxWidth, 2, 4, 1, 1);

        label_17 = new QLabel(groupBox_2);
        label_17->setObjectName(QStringLiteral("label_17"));

        gridLayout_5->addWidget(label_17, 7, 0, 1, 1);

        minGray = new QLineEdit(groupBox_2);
        minGray->setObjectName(QStringLiteral("minGray"));
        minGray->setInputMethodHints(Qt::ImhDigitsOnly);

        gridLayout_5->addWidget(minGray, 5, 2, 1, 1);

        smothWidth = new QLineEdit(groupBox_2);
        smothWidth->setObjectName(QStringLiteral("smothWidth"));
        smothWidth->setInputMethodHints(Qt::ImhDigitsOnly);

        gridLayout_5->addWidget(smothWidth, 7, 2, 1, 1);

        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout_5->addWidget(label_9, 9, 0, 1, 1);

        contrast = new QLineEdit(groupBox_2);
        contrast->setObjectName(QStringLiteral("contrast"));
        contrast->setInputMethodHints(Qt::ImhDigitsOnly);

        gridLayout_5->addWidget(contrast, 8, 2, 1, 1);

        checkMinArea = new QLineEdit(groupBox_2);
        checkMinArea->setObjectName(QStringLiteral("checkMinArea"));

        gridLayout_5->addWidget(checkMinArea, 0, 2, 1, 1);

        badMinArea = new QLineEdit(groupBox_2);
        badMinArea->setObjectName(QStringLiteral("badMinArea"));
        badMinArea->setInputMethodHints(Qt::ImhDigitsOnly);

        gridLayout_5->addWidget(badMinArea, 1, 2, 1, 1);

        label_11 = new QLabel(groupBox_2);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout_5->addWidget(label_11, 3, 0, 1, 1);

        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_5->addWidget(label_6, 0, 0, 1, 1);

        badMinWidth = new QLineEdit(groupBox_2);
        badMinWidth->setObjectName(QStringLiteral("badMinWidth"));
        badMinWidth->setInputMethodHints(Qt::ImhDigitsOnly);

        gridLayout_5->addWidget(badMinWidth, 2, 2, 1, 1);

        smothHeight = new QLineEdit(groupBox_2);
        smothHeight->setObjectName(QStringLiteral("smothHeight"));
        smothHeight->setInputMethodHints(Qt::ImhDigitsOnly);

        gridLayout_5->addWidget(smothHeight, 7, 4, 1, 1);

        checkMaxArea = new QLineEdit(groupBox_2);
        checkMaxArea->setObjectName(QStringLiteral("checkMaxArea"));

        gridLayout_5->addWidget(checkMaxArea, 0, 4, 1, 1);

        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_5->addWidget(label_8, 1, 0, 1, 1);

        label_15 = new QLabel(groupBox_2);
        label_15->setObjectName(QStringLiteral("label_15"));

        gridLayout_5->addWidget(label_15, 5, 0, 1, 1);

        maxGray = new QLineEdit(groupBox_2);
        maxGray->setObjectName(QStringLiteral("maxGray"));
        maxGray->setInputMethodHints(Qt::ImhDigitsOnly);

        gridLayout_5->addWidget(maxGray, 5, 4, 1, 1);

        label_18 = new QLabel(groupBox_2);
        label_18->setObjectName(QStringLiteral("label_18"));

        gridLayout_5->addWidget(label_18, 13, 0, 1, 1);

        badMaxradius = new QLineEdit(groupBox_2);
        badMaxradius->setObjectName(QStringLiteral("badMaxradius"));
        badMaxradius->setInputMethodHints(Qt::ImhDigitsOnly);

        gridLayout_5->addWidget(badMaxradius, 4, 4, 1, 1);

        badMaxHeight = new QLineEdit(groupBox_2);
        badMaxHeight->setObjectName(QStringLiteral("badMaxHeight"));
        badMaxHeight->setInputMethodHints(Qt::ImhDigitsOnly);

        gridLayout_5->addWidget(badMaxHeight, 3, 4, 1, 1);

        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_5->addWidget(label_7, 8, 0, 1, 1);

        doubleTurn = new QCheckBox(groupBox_2);
        doubleTurn->setObjectName(QStringLiteral("doubleTurn"));

        gridLayout_5->addWidget(doubleTurn, 15, 0, 1, 1);


        gridLayout_4->addWidget(groupBox_2, 1, 0, 1, 2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer, 1, 3, 1, 2);

        default_2 = new QPushButton(tab_3);
        default_2->setObjectName(QStringLiteral("default_2"));

        gridLayout_4->addWidget(default_2, 1, 2, 1, 1);

        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        gridLayout_8 = new QGridLayout(tab_4);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        groupBox_5 = new QGroupBox(tab_4);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        gridLayout_9 = new QGridLayout(groupBox_5);
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        cameraCheck = new QCheckBox(groupBox_5);
        cameraCheck->setObjectName(QStringLiteral("cameraCheck"));

        gridLayout_9->addWidget(cameraCheck, 0, 0, 1, 1);

        label_12 = new QLabel(groupBox_5);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout_9->addWidget(label_12, 1, 0, 1, 1);

        label_13 = new QLabel(groupBox_5);
        label_13->setObjectName(QStringLiteral("label_13"));

        gridLayout_9->addWidget(label_13, 2, 0, 1, 1);

        cameraName = new QLineEdit(groupBox_5);
        cameraName->setObjectName(QStringLiteral("cameraName"));

        gridLayout_9->addWidget(cameraName, 1, 1, 1, 1);

        cameraDevice = new QLineEdit(groupBox_5);
        cameraDevice->setObjectName(QStringLiteral("cameraDevice"));

        gridLayout_9->addWidget(cameraDevice, 2, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_9->addItem(horizontalSpacer_2, 1, 2, 1, 1);

        label_14 = new QLabel(groupBox_5);
        label_14->setObjectName(QStringLiteral("label_14"));

        gridLayout_9->addWidget(label_14, 3, 0, 1, 1);

        camera_exposureTime = new QSpinBox(groupBox_5);
        camera_exposureTime->setObjectName(QStringLiteral("camera_exposureTime"));
        camera_exposureTime->setMinimum(650);
        camera_exposureTime->setMaximum(65535);

        gridLayout_9->addWidget(camera_exposureTime, 3, 1, 1, 1);


        gridLayout_8->addWidget(groupBox_5, 0, 0, 1, 1);

        tabWidget->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QStringLiteral("tab_5"));
        formLayoutWidget = new QWidget(tab_5);
        formLayoutWidget->setObjectName(QStringLiteral("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(10, 0, 288, 502));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout->setRowWrapPolicy(QFormLayout::DontWrapRows);
        formLayout->setHorizontalSpacing(20);
        formLayout->setVerticalSpacing(12);
        formLayout->setContentsMargins(0, 0, 0, 0);
        label_25 = new QLabel(formLayoutWidget);
        label_25->setObjectName(QStringLiteral("label_25"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_25);

        select_device = new QComboBox(formLayoutWidget);
        select_device->setObjectName(QStringLiteral("select_device"));

        formLayout->setWidget(0, QFormLayout::FieldRole, select_device);

        label_21 = new QLabel(formLayoutWidget);
        label_21->setObjectName(QStringLiteral("label_21"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_21);

        profileCount = new QSpinBox(formLayoutWidget);
        profileCount->setObjectName(QStringLiteral("profileCount"));
        profileCount->setMaximum(10000);
        profileCount->setSingleStep(10);
        profileCount->setValue(1000);

        formLayout->setWidget(1, QFormLayout::FieldRole, profileCount);

        label_22 = new QLabel(formLayoutWidget);
        label_22->setObjectName(QStringLiteral("label_22"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_22);

        exposure = new QComboBox(formLayoutWidget);
        exposure->setObjectName(QStringLiteral("exposure"));

        formLayout->setWidget(2, QFormLayout::FieldRole, exposure);

        label_24 = new QLabel(formLayoutWidget);
        label_24->setObjectName(QStringLiteral("label_24"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_24);

        resolution = new QComboBox(formLayoutWidget);
        resolution->setObjectName(QStringLiteral("resolution"));

        formLayout->setWidget(4, QFormLayout::FieldRole, resolution);

        label_20 = new QLabel(formLayoutWidget);
        label_20->setObjectName(QStringLiteral("label_20"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_20);

        resampleValue = new QComboBox(formLayoutWidget);
        resampleValue->setObjectName(QStringLiteral("resampleValue"));

        formLayout->setWidget(5, QFormLayout::FieldRole, resampleValue);

        label_27 = new QLabel(formLayoutWidget);
        label_27->setObjectName(QStringLiteral("label_27"));

        formLayout->setWidget(6, QFormLayout::LabelRole, label_27);

        median = new QComboBox(formLayoutWidget);
        median->setObjectName(QStringLiteral("median"));

        formLayout->setWidget(6, QFormLayout::FieldRole, median);

        label_28 = new QLabel(formLayoutWidget);
        label_28->setObjectName(QStringLiteral("label_28"));

        formLayout->setWidget(7, QFormLayout::LabelRole, label_28);

        average = new QComboBox(formLayoutWidget);
        average->setObjectName(QStringLiteral("average"));

        formLayout->setWidget(7, QFormLayout::FieldRole, average);

        label_30 = new QLabel(formLayoutWidget);
        label_30->setObjectName(QStringLiteral("label_30"));

        formLayout->setWidget(8, QFormLayout::LabelRole, label_30);

        trigger = new QComboBox(formLayoutWidget);
        trigger->setObjectName(QStringLiteral("trigger"));

        formLayout->setWidget(8, QFormLayout::FieldRole, trigger);

        label_31 = new QLabel(formLayoutWidget);
        label_31->setObjectName(QStringLiteral("label_31"));

        formLayout->setWidget(9, QFormLayout::LabelRole, label_31);

        triggerMode = new QComboBox(formLayoutWidget);
        triggerMode->setObjectName(QStringLiteral("triggerMode"));

        formLayout->setWidget(9, QFormLayout::FieldRole, triggerMode);

        label_32 = new QLabel(formLayoutWidget);
        label_32->setObjectName(QStringLiteral("label_32"));

        formLayout->setWidget(10, QFormLayout::LabelRole, label_32);

        triggerSource = new QComboBox(formLayoutWidget);
        triggerSource->setObjectName(QStringLiteral("triggerSource"));
        triggerSource->setToolTipDuration(-1);

        formLayout->setWidget(10, QFormLayout::FieldRole, triggerSource);

        label_33 = new QLabel(formLayoutWidget);
        label_33->setObjectName(QStringLiteral("label_33"));

        formLayout->setWidget(11, QFormLayout::LabelRole, label_33);

        triggerPolarity = new QComboBox(formLayoutWidget);
        triggerPolarity->setObjectName(QStringLiteral("triggerPolarity"));

        formLayout->setWidget(11, QFormLayout::FieldRole, triggerPolarity);

        label_35 = new QLabel(formLayoutWidget);
        label_35->setObjectName(QStringLiteral("label_35"));

        formLayout->setWidget(12, QFormLayout::LabelRole, label_35);

        voltage = new QComboBox(formLayoutWidget);
        voltage->setObjectName(QStringLiteral("voltage"));

        formLayout->setWidget(12, QFormLayout::FieldRole, voltage);

        label_36 = new QLabel(formLayoutWidget);
        label_36->setObjectName(QStringLiteral("label_36"));

        formLayout->setWidget(13, QFormLayout::LabelRole, label_36);

        digitalInputs = new QComboBox(formLayoutWidget);
        digitalInputs->setObjectName(QStringLiteral("digitalInputs"));

        formLayout->setWidget(13, QFormLayout::FieldRole, digitalInputs);

        label_23 = new QLabel(formLayoutWidget);
        label_23->setObjectName(QStringLiteral("label_23"));

        formLayout->setWidget(14, QFormLayout::LabelRole, label_23);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        autoThreshold = new QComboBox(formLayoutWidget);
        autoThreshold->setObjectName(QStringLiteral("autoThreshold"));

        horizontalLayout_3->addWidget(autoThreshold);

        threshold = new QSpinBox(formLayoutWidget);
        threshold->setObjectName(QStringLiteral("threshold"));
        threshold->setMaximum(255);

        horizontalLayout_3->addWidget(threshold);


        formLayout->setLayout(14, QFormLayout::FieldRole, horizontalLayout_3);

        label_26 = new QLabel(formLayoutWidget);
        label_26->setObjectName(QStringLiteral("label_26"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_26);

        rate = new QSpinBox(formLayoutWidget);
        rate->setObjectName(QStringLiteral("rate"));
        rate->setMinimum(1);
        rate->setMaximum(1000);
        rate->setValue(100);

        formLayout->setWidget(3, QFormLayout::FieldRole, rate);

        debug = new QTextBrowser(tab_5);
        debug->setObjectName(QStringLiteral("debug"));
        debug->setGeometry(QRect(330, 30, 261, 401));
        label_37 = new QLabel(tab_5);
        label_37->setObjectName(QStringLiteral("label_37"));
        label_37->setGeometry(QRect(330, 10, 54, 12));
        readSet = new QPushButton(tab_5);
        readSet->setObjectName(QStringLiteral("readSet"));
        readSet->setGeometry(QRect(280, 470, 91, 23));
        connecct = new QPushButton(tab_5);
        connecct->setObjectName(QStringLiteral("connecct"));
        connecct->setGeometry(QRect(240, 0, 41, 23));
        testValue = new QDoubleSpinBox(tab_5);
        testValue->setObjectName(QStringLiteral("testValue"));
        testValue->setGeometry(QRect(280, 440, 62, 22));
        testValue->setSingleStep(0.001);
        testValue->setValue(0.01);
        tabWidget->addTab(tab_5, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QStringLiteral("tab_6"));
        formLayoutWidget_2 = new QWidget(tab_6);
        formLayoutWidget_2->setObjectName(QStringLiteral("formLayoutWidget_2"));
        formLayoutWidget_2->setGeometry(QRect(10, 10, 301, 501));
        formLayout_2 = new QFormLayout(formLayoutWidget_2);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        formLayout_2->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout_2->setContentsMargins(0, 0, 0, 0);
        label_34 = new QLabel(formLayoutWidget_2);
        label_34->setObjectName(QStringLiteral("label_34"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_34);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        ip32 = new QSpinBox(formLayoutWidget_2);
        ip32->setObjectName(QStringLiteral("ip32"));
        ip32->setMinimum(0);
        ip32->setMaximum(255);
        ip32->setValue(192);

        horizontalLayout_6->addWidget(ip32);

        ip24 = new QSpinBox(formLayoutWidget_2);
        ip24->setObjectName(QStringLiteral("ip24"));
        ip24->setMinimum(0);
        ip24->setMaximum(255);
        ip24->setValue(168);

        horizontalLayout_6->addWidget(ip24);

        ip16 = new QSpinBox(formLayoutWidget_2);
        ip16->setObjectName(QStringLiteral("ip16"));
        ip16->setMaximum(255);

        horizontalLayout_6->addWidget(ip16);

        ip0 = new QSpinBox(formLayoutWidget_2);
        ip0->setObjectName(QStringLiteral("ip0"));
        ip0->setMaximum(255);
        ip0->setValue(1);

        horizontalLayout_6->addWidget(ip0);


        formLayout_2->setLayout(2, QFormLayout::FieldRole, horizontalLayout_6);

        label_41 = new QLabel(formLayoutWidget_2);
        label_41->setObjectName(QStringLiteral("label_41"));

        formLayout_2->setWidget(3, QFormLayout::LabelRole, label_41);

        dataPort = new QSpinBox(formLayoutWidget_2);
        dataPort->setObjectName(QStringLiteral("dataPort"));
        dataPort->setMinimum(1024);
        dataPort->setMaximum(65535);
        dataPort->setValue(24692);

        formLayout_2->setWidget(3, QFormLayout::FieldRole, dataPort);

        label_40 = new QLabel(formLayoutWidget_2);
        label_40->setObjectName(QStringLiteral("label_40"));

        formLayout_2->setWidget(4, QFormLayout::LabelRole, label_40);

        commandPort = new QSpinBox(formLayoutWidget_2);
        commandPort->setObjectName(QStringLiteral("commandPort"));
        commandPort->setMinimum(1024);
        commandPort->setMaximum(65535);
        commandPort->setValue(24691);

        formLayout_2->setWidget(4, QFormLayout::FieldRole, commandPort);

        label_38 = new QLabel(formLayoutWidget_2);
        label_38->setObjectName(QStringLiteral("label_38"));

        formLayout_2->setWidget(5, QFormLayout::LabelRole, label_38);

        freq = new QSpinBox(formLayoutWidget_2);
        freq->setObjectName(QStringLiteral("freq"));
        freq->setMinimum(1);
        freq->setMaximum(10000);
        freq->setValue(10);

        formLayout_2->setWidget(5, QFormLayout::FieldRole, freq);

        usb = new QRadioButton(formLayoutWidget_2);
        usb->setObjectName(QStringLiteral("usb"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, usb);

        Ethernet = new QRadioButton(formLayoutWidget_2);
        Ethernet->setObjectName(QStringLiteral("Ethernet"));
        Ethernet->setChecked(true);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, Ethernet);

        tabWidget->addTab(tab_6, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);

#ifndef QT_NO_SHORTCUT
        label_2->setBuddy(path);
        label->setBuddy(robotIp);
        label_3->setBuddy(robotPort);
        label_4->setBuddy(robotIp);
        label_5->setBuddy(robotPort);
#endif // QT_NO_SHORTCUT

        retranslateUi(mySettings);
        QObject::connect(Button_Yes, SIGNAL(clicked()), mySettings, SLOT(accept()));
        QObject::connect(pushButton_Cancel, SIGNAL(clicked()), mySettings, SLOT(close()));

        tabWidget->setCurrentIndex(2);
        triggerSource->setCurrentIndex(1);
        triggerPolarity->setCurrentIndex(1);
        digitalInputs->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(mySettings);
    } // setupUi

    void retranslateUi(QDialog *mySettings)
    {
        mySettings->setWindowTitle(QApplication::translate("mySettings", "\347\275\221\347\273\234\345\217\202\346\225\260", 0));
        groupBox->setTitle(QString());
        Button_Yes->setText(QApplication::translate("mySettings", "\347\241\256\345\256\232", 0));
        pushButton_Cancel->setText(QApplication::translate("mySettings", "\345\217\226\346\266\210", 0));
        groupBox_3->setTitle(QString());
        open->setText(QApplication::translate("mySettings", "\346\211\223\345\274\200", 0));
        path->setText(QApplication::translate("mySettings", "D:/image", 0));
        label_2->setText(QApplication::translate("mySettings", "\346\226\207\344\273\266\350\267\257\345\276\204\357\274\232", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("mySettings", "\350\267\257\345\276\204\350\256\276\347\275\256", 0));
        groupBox_4->setTitle(QString());
        label->setText(QApplication::translate("mySettings", "\346\234\272\346\242\260\346\211\213IP\345\234\260\345\235\200:", 0));
        robotIp->setText(QApplication::translate("mySettings", "192.168.1.120", 0));
        label_3->setText(QApplication::translate("mySettings", "\347\253\257\345\217\243:", 0));
        robotPort->setText(QApplication::translate("mySettings", "5000", 0));
        label_4->setText(QApplication::translate("mySettings", "  \347\233\270\346\234\272IP\345\234\260\345\235\200:", 0));
        label_5->setText(QApplication::translate("mySettings", "udp\347\253\257\345\217\243:", 0));
        cameraIp->setText(QApplication::translate("mySettings", "192.168.1.120", 0));
        cameraPort->setText(QApplication::translate("mySettings", "6001", 0));
        label_19->setText(QApplication::translate("mySettings", "\346\234\254\345\234\260UDP\347\253\257\345\217\243:", 0));
        udpPort->setText(QApplication::translate("mySettings", "6002", 0));
        groupBox_6->setTitle(QApplication::translate("mySettings", "\346\265\213\350\257\225\347\275\221\347\273\234", 0));
        sendButton->setText(QApplication::translate("mySettings", "\345\217\221\351\200\201\346\266\210\346\201\257", 0));
        label_29->setText(QApplication::translate("mySettings", "\346\216\245\346\224\266:", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("mySettings", "\347\275\221\347\273\234\350\256\276\347\275\256", 0));
        groupBox_2->setTitle(QString());
        erosion->setText(QApplication::translate("mySettings", "200", 0));
        label_16->setText(QApplication::translate("mySettings", "\347\274\272\351\231\267\345\215\212\345\276\204", 0));
        grayDvalue->setText(QApplication::translate("mySettings", "20", 0));
        label_39->setText(QApplication::translate("mySettings", "\345\233\276\347\211\207\346\225\260\351\207\217", 0));
        badMaxArea->setText(QApplication::translate("mySettings", "200", 0));
        badMinHeight->setText(QApplication::translate("mySettings", "2", 0));
        label_10->setText(QApplication::translate("mySettings", "\347\274\272\351\231\267\351\231\220\345\256\232\345\256\275\345\272\246(pix)", 0));
        badMinRadius->setText(QApplication::translate("mySettings", "1", 0));
        badMaxWidth->setText(QApplication::translate("mySettings", "40", 0));
        label_17->setText(QApplication::translate("mySettings", "\346\250\241\347\263\212\347\263\273\346\225\260", 0));
        minGray->setText(QApplication::translate("mySettings", "100", 0));
        smothWidth->setText(QApplication::translate("mySettings", "7", 0));
        label_9->setText(QApplication::translate("mySettings", "\347\201\260\345\272\246\345\200\274\345\267\256\345\200\274", 0));
        contrast->setText(QApplication::translate("mySettings", "2", 0));
        checkMinArea->setText(QApplication::translate("mySettings", "2000000", 0));
        badMinArea->setText(QApplication::translate("mySettings", "3", 0));
        label_11->setText(QApplication::translate("mySettings", "\347\274\272\351\231\267\351\231\220\345\256\232\351\253\230\345\272\246(pix)", 0));
        label_6->setText(QApplication::translate("mySettings", "\350\242\253\346\265\213\347\211\251\351\235\242\347\247\257(pix)", 0));
        badMinWidth->setText(QApplication::translate("mySettings", "2", 0));
        smothHeight->setText(QApplication::translate("mySettings", "7", 0));
        checkMaxArea->setText(QApplication::translate("mySettings", "45700000", 0));
        label_8->setText(QApplication::translate("mySettings", "\347\274\272\351\231\267\351\231\220\345\256\232\351\235\242\347\247\257(pix)", 0));
        label_15->setText(QApplication::translate("mySettings", "\344\272\214\345\200\274\345\214\226\350\214\203\345\233\264:", 0));
        maxGray->setText(QApplication::translate("mySettings", "255", 0));
        label_18->setText(QApplication::translate("mySettings", "\350\205\220\350\232\200\347\263\273\346\225\260", 0));
        badMaxradius->setText(QApplication::translate("mySettings", "10", 0));
        badMaxHeight->setText(QApplication::translate("mySettings", "40", 0));
        label_7->setText(QApplication::translate("mySettings", "\345\257\271\346\257\224\345\272\246", 0));
        doubleTurn->setText(QApplication::translate("mySettings", "\345\217\214\346\225\260\347\277\273\350\275\254", 0));
        default_2->setText(QApplication::translate("mySettings", "\346\201\242\345\244\215\351\273\230\350\256\244", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("mySettings", "\346\243\200\346\265\213\350\256\276\347\275\256", 0));
        groupBox_5->setTitle(QString());
        cameraCheck->setText(QApplication::translate("mySettings", "\345\220\257\347\224\250\347\233\270\346\234\272", 0));
        label_12->setText(QApplication::translate("mySettings", "Name:", 0));
        label_13->setText(QApplication::translate("mySettings", "Device:", 0));
        cameraName->setText(QApplication::translate("mySettings", "DirectShow", 0));
        cameraDevice->setText(QApplication::translate("mySettings", "TOSHIBA Web Camera - HD", 0));
        label_14->setText(QApplication::translate("mySettings", "ExposureTime:", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("mySettings", "\347\233\270\346\234\272\350\256\276\347\275\256", 0));
        label_25->setText(QApplication::translate("mySettings", "\351\200\211\346\213\251\350\256\276\345\244\207:", 0));
        select_device->clear();
        select_device->insertItems(0, QStringList()
         << QApplication::translate("mySettings", "0", 0)
        );
        label_21->setText(QApplication::translate("mySettings", "\351\207\207\346\240\267\346\254\241\346\225\260:", 0));
        label_22->setText(QApplication::translate("mySettings", "\346\233\235\345\205\211\346\227\266\351\227\264:", 0));
        exposure->clear();
        exposure->insertItems(0, QStringList()
         << QApplication::translate("mySettings", "0.01", 0)
         << QApplication::translate("mySettings", "0.02", 0)
         << QApplication::translate("mySettings", "0.05", 0)
         << QApplication::translate("mySettings", "0.10", 0)
         << QApplication::translate("mySettings", "0.20", 0)
         << QApplication::translate("mySettings", "0.35", 0)
         << QApplication::translate("mySettings", "0.50", 0)
         << QApplication::translate("mySettings", "0.75", 0)
         << QApplication::translate("mySettings", "1.00", 0)
         << QApplication::translate("mySettings", "1.50", 0)
         << QApplication::translate("mySettings", "2.0", 0)
         << QApplication::translate("mySettings", "5.0", 0)
         << QApplication::translate("mySettings", "10.0", 0)
         << QApplication::translate("mySettings", "20.0", 0)
         << QApplication::translate("mySettings", "40.0", 0)
        );
        label_24->setText(QApplication::translate("mySettings", "\345\210\206\350\276\250\347\216\207:", 0));
        label_20->setText(QApplication::translate("mySettings", "\351\207\215\351\207\207\346\240\267:", 0));
        resampleValue->clear();
        resampleValue->insertItems(0, QStringList()
         << QApplication::translate("mySettings", "disable", 0)
         << QApplication::translate("mySettings", "1\347\272\247(\346\234\200\345\260\217)", 0)
         << QApplication::translate("mySettings", "2\347\272\247", 0)
         << QApplication::translate("mySettings", "3\347\272\247", 0)
         << QApplication::translate("mySettings", "4\347\272\247", 0)
         << QApplication::translate("mySettings", "5\347\272\247", 0)
         << QApplication::translate("mySettings", "6\347\272\247", 0)
         << QApplication::translate("mySettings", "7\347\272\247(\346\234\200\345\244\247)", 0)
        );
        label_27->setText(QApplication::translate("mySettings", "\344\270\255\345\200\274\346\273\244\346\263\242:", 0));
        median->clear();
        median->insertItems(0, QStringList()
         << QApplication::translate("mySettings", "disable", 0)
         << QApplication::translate("mySettings", "3", 0)
         << QApplication::translate("mySettings", "5", 0)
         << QApplication::translate("mySettings", "7", 0)
        );
        label_28->setText(QApplication::translate("mySettings", "\345\235\207\345\200\274\346\273\244\346\263\242:", 0));
        average->clear();
        average->insertItems(0, QStringList()
         << QApplication::translate("mySettings", "disable", 0)
         << QApplication::translate("mySettings", "3", 0)
         << QApplication::translate("mySettings", "5", 0)
         << QApplication::translate("mySettings", "7", 0)
        );
        label_30->setText(QApplication::translate("mySettings", "\345\220\257\345\212\250\345\244\226\351\203\250\350\247\246\345\217\221:", 0));
        trigger->clear();
        trigger->insertItems(0, QStringList()
         << QApplication::translate("mySettings", "disable", 0)
         << QApplication::translate("mySettings", "enable", 0)
        );
        label_31->setText(QApplication::translate("mySettings", "\350\247\246\345\217\221\346\250\241\345\274\217:", 0));
        triggerMode->clear();
        triggerMode->insertItems(0, QStringList()
         << QApplication::translate("mySettings", "edge mode", 0)
         << QApplication::translate("mySettings", "pulse mode", 0)
         << QApplication::translate("mySettings", "gated mode", 0)
         << QApplication::translate("mySettings", "encoder mode", 0)
        );
        label_32->setText(QApplication::translate("mySettings", "\350\247\246\345\217\221\346\272\220:", 0));
        triggerSource->clear();
        triggerSource->insertItems(0, QStringList()
         << QApplication::translate("mySettings", "RS422", 0)
         << QApplication::translate("mySettings", "Input In1 or encoder", 0)
        );
#ifndef QT_NO_TOOLTIP
        triggerSource->setToolTip(QApplication::translate("mySettings", "<html><head/><body><p>0 RS422</p><p>1 Input In1 (Mode 0, 1 and 2) or encoder (Mode 3)</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        label_33->setText(QApplication::translate("mySettings", "\346\236\201\346\200\247:", 0));
        triggerPolarity->clear();
        triggerPolarity->insertItems(0, QStringList()
         << QApplication::translate("mySettings", " 0 low active", 0)
         << QApplication::translate("mySettings", "1 high active", 0)
        );
        label_35->setText(QApplication::translate("mySettings", "\346\225\260\345\255\227\350\276\223\345\205\245\347\224\265\345\216\213:", 0));
        voltage->clear();
        voltage->insertItems(0, QStringList()
         << QApplication::translate("mySettings", "TTL, 5V", 0)
         << QApplication::translate("mySettings", "HTL, 24V", 0)
        );
#ifndef QT_NO_TOOLTIP
        voltage->setToolTip(QApplication::translate("mySettings", "<html><head/><body><p><br/></p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        label_36->setText(QApplication::translate("mySettings", "\346\225\260\345\255\227\350\276\223\345\205\245\345\212\237\350\203\275:", 0));
        digitalInputs->clear();
        digitalInputs->insertItems(0, QStringList()
         << QApplication::translate("mySettings", "\347\274\226\347\240\201\345\231\250\357\274\214\346\255\243\346\262\277\346\214\207\346\225\260\350\277\275\350\270\252", 0)
         << QApplication::translate("mySettings", "\347\274\226\347\240\201\345\231\250\357\274\214\345\244\226\351\203\250\350\247\246\345\217\221", 0)
         << QApplication::translate("mySettings", "\345\244\226\351\203\250\350\247\246\345\217\221", 0)
         << QApplication::translate("mySettings", "\345\244\226\351\203\250\350\247\246\345\217\221 + \347\224\250\346\210\267\346\250\241\345\274\217\345\212\240\350\275\275\344\270\244\344\275\215", 0)
         << QApplication::translate("mySettings", "\347\224\250\346\210\267\346\250\241\345\274\217\345\212\240\350\275\275\344\270\211\344\275\215", 0)
         << QApplication::translate("mySettings", "\346\217\222\345\205\245\346\227\266\351\227\264\346\210\263", 0)
        );
#ifndef QT_NO_TOOLTIP
        digitalInputs->setToolTip(QApplication::translate("mySettings", "<html><head/><body><p>0 encoder, positive edge of index track (*)</p><p>1 encoder with external trigger input (*)</p><p>2 external trigger input</p><p>3 ext. trigger + two bits for user mode loading</p><p>4 three bits for user mode loading</p><p>5 insert into timestamp</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        label_23->setText(QApplication::translate("mySettings", "threshold:", 0));
        autoThreshold->clear();
        autoThreshold->insertItems(0, QStringList()
         << QApplication::translate("mySettings", "absolute", 0)
         << QApplication::translate("mySettings", "auto", 0)
        );
        label_26->setText(QApplication::translate("mySettings", "\345\270\247\347\216\207:", 0));
        label_37->setText(QApplication::translate("mySettings", "debug\350\276\223\345\207\272", 0));
        readSet->setText(QApplication::translate("mySettings", "\350\257\273\345\217\226\345\275\223\345\211\215\351\205\215\347\275\256", 0));
        connecct->setText(QApplication::translate("mySettings", "\350\277\236\346\216\245", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QApplication::translate("mySettings", "\346\277\200\345\205\211\350\256\276\347\275\256", 0));
        label_34->setText(QApplication::translate("mySettings", "IP:", 0));
        label_41->setText(QApplication::translate("mySettings", "\344\274\240\350\276\223\347\253\257\345\217\243:", 0));
        label_40->setText(QApplication::translate("mySettings", "\346\216\247\345\210\266\347\253\257\345\217\243:", 0));
        label_38->setText(QApplication::translate("mySettings", "\345\233\236\350\260\203\351\242\221\347\216\207:", 0));
        usb->setText(QApplication::translate("mySettings", "USB", 0));
        Ethernet->setText(QApplication::translate("mySettings", "Ethernet", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_6), QApplication::translate("mySettings", "\345\237\272\346\201\251\346\226\257\346\277\200\345\205\211\350\256\276\347\275\256", 0));
    } // retranslateUi

};

namespace Ui {
    class mySettings: public Ui_mySettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGDIALOG_H
