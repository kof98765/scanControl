/********************************************************************************
** Form generated from reading UI file 'data_analyze.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATA_ANALYZE_H
#define UI_DATA_ANALYZE_H

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
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_data_analyze
{
public:
    QGridLayout *gridLayout_2;
    QGroupBox *box;
    QGridLayout *gridLayout_8;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer;
    QGraphicsView *tvplot;

    void setupUi(QDialog *data_analyze)
    {
        if (data_analyze->objectName().isEmpty())
            data_analyze->setObjectName(QStringLiteral("data_analyze"));
        data_analyze->resize(514, 243);
        gridLayout_2 = new QGridLayout(data_analyze);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        box = new QGroupBox(data_analyze);
        box->setObjectName(QStringLiteral("box"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(10);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        box->setFont(font);
        box->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 255);\n"
"font: 10pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        gridLayout_8 = new QGridLayout(box);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        pushButton = new QPushButton(box);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout_8->addWidget(pushButton, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_8->addItem(horizontalSpacer, 0, 1, 1, 1);

        tvplot = new QGraphicsView(box);
        tvplot->setObjectName(QStringLiteral("tvplot"));
        tvplot->setMinimumSize(QSize(0, 0));
        tvplot->setStyleSheet(QString::fromUtf8("font: 9pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color: rgb(0, 0, 0);"));

        gridLayout_8->addWidget(tvplot, 1, 0, 1, 2);


        gridLayout_2->addWidget(box, 0, 0, 1, 1);


        retranslateUi(data_analyze);

        QMetaObject::connectSlotsByName(data_analyze);
    } // setupUi

    void retranslateUi(QDialog *data_analyze)
    {
        data_analyze->setWindowTitle(QApplication::translate("data_analyze", "\346\225\260\346\215\256\345\210\206\346\236\220\346\212\245\345\221\212", 0));
        box->setTitle(QString());
        pushButton->setText(QApplication::translate("data_analyze", "\345\257\274\345\207\272\345\233\276\350\241\250", 0));
    } // retranslateUi

};

namespace Ui {
    class data_analyze: public Ui_data_analyze {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATA_ANALYZE_H
