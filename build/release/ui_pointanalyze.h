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
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_pointAnalyze
{
public:
    QGraphicsView *base;

    void setupUi(QDialog *pointAnalyze)
    {
        if (pointAnalyze->objectName().isEmpty())
            pointAnalyze->setObjectName(QStringLiteral("pointAnalyze"));
        pointAnalyze->resize(364, 258);
        base = new QGraphicsView(pointAnalyze);
        base->setObjectName(QStringLiteral("base"));
        base->setGeometry(QRect(10, 10, 341, 231));
        base->setDragMode(QGraphicsView::RubberBandDrag);

        retranslateUi(pointAnalyze);

        QMetaObject::connectSlotsByName(pointAnalyze);
    } // setupUi

    void retranslateUi(QDialog *pointAnalyze)
    {
        pointAnalyze->setWindowTitle(QApplication::translate("pointAnalyze", "\347\202\271\344\272\221\346\225\260\346\215\256\345\210\206\346\236\220", 0));
    } // retranslateUi

};

namespace Ui {
    class pointAnalyze: public Ui_pointAnalyze {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POINTANALYZE_H
