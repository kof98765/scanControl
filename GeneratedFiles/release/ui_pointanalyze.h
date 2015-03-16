/********************************************************************************
** Form generated from reading UI file 'pointanalyze.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POINTANALYZE_H
#define UI_POINTANALYZE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_pointAnalyze
{
public:
    QGraphicsView *base;
    QGroupBox *groupBox;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QPushButton *loadButton;
    QPushButton *preFrame;
    QPushButton *reset;
    QPushButton *pushButton;
    QPushButton *nextFrame;
    QSpinBox *numFrame;

    void setupUi(QDialog *pointAnalyze)
    {
        if (pointAnalyze->objectName().isEmpty())
            pointAnalyze->setObjectName(QStringLiteral("pointAnalyze"));
        pointAnalyze->resize(895, 547);
        base = new QGraphicsView(pointAnalyze);
        base->setObjectName(QStringLiteral("base"));
        base->setGeometry(QRect(0, 0, 901, 381));
        base->setDragMode(QGraphicsView::RubberBandDrag);
        groupBox = new QGroupBox(pointAnalyze);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 390, 871, 151));
        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 10, 371, 131));
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        loadButton = new QPushButton(groupBox_2);
        loadButton->setObjectName(QStringLiteral("loadButton"));

        gridLayout->addWidget(loadButton, 0, 0, 1, 1);

        preFrame = new QPushButton(groupBox_2);
        preFrame->setObjectName(QStringLiteral("preFrame"));

        gridLayout->addWidget(preFrame, 1, 0, 1, 1);

        reset = new QPushButton(groupBox_2);
        reset->setObjectName(QStringLiteral("reset"));

        gridLayout->addWidget(reset, 0, 2, 1, 1);

        pushButton = new QPushButton(groupBox_2);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 0, 1, 1, 1);

        nextFrame = new QPushButton(groupBox_2);
        nextFrame->setObjectName(QStringLiteral("nextFrame"));

        gridLayout->addWidget(nextFrame, 1, 2, 1, 1);

        numFrame = new QSpinBox(groupBox_2);
        numFrame->setObjectName(QStringLiteral("numFrame"));
        numFrame->setMaximum(9999);

        gridLayout->addWidget(numFrame, 1, 1, 1, 1);


        retranslateUi(pointAnalyze);

        QMetaObject::connectSlotsByName(pointAnalyze);
    } // setupUi

    void retranslateUi(QDialog *pointAnalyze)
    {
        pointAnalyze->setWindowTitle(QApplication::translate("pointAnalyze", "\347\202\271\344\272\221\346\225\260\346\215\256\345\210\206\346\236\220", 0));
        groupBox->setTitle(QString());
        groupBox_2->setTitle(QApplication::translate("pointAnalyze", "\346\250\241\346\213\237", 0));
        loadButton->setText(QApplication::translate("pointAnalyze", "\345\212\240\350\275\275\346\226\207\344\273\266", 0));
        preFrame->setText(QApplication::translate("pointAnalyze", "\344\270\212\344\270\200\345\270\247", 0));
        reset->setText(QApplication::translate("pointAnalyze", "\345\244\215\344\275\215", 0));
        pushButton->setText(QApplication::translate("pointAnalyze", "\350\277\236\347\273\255\350\257\273\345\217\226", 0));
        nextFrame->setText(QApplication::translate("pointAnalyze", "\344\270\213\344\270\200\345\270\247", 0));
    } // retranslateUi

};

namespace Ui {
    class pointAnalyze: public Ui_pointAnalyze {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POINTANALYZE_H
