#ifndef IMGLIST_H
#define IMGLIST_H

#include <QObject>
#include "HalconCpp.h"
#include <Qlabel>
#include <QHBoxLayout>
#include <QEvent>
#include <QMouseEvent>
#include <QDebug>
using namespace Halcon;
class clickLabel:public QLabel
{
    Q_OBJECT
public:
    clickLabel(QLabel *parent=0);
protected:
    bool eventFilter(QObject *obj, QEvent *e);
signals:
    void click();
};
class imgListView : public QObject
{
    Q_OBJECT
public:
    imgListView(QObject *parent = 0);
protected:

private:
    QHBoxLayout *layout;
    QList<Hobject*> imgList;
    QList<clickLabel*> labelList;
    QList<HTuple> winList;
    int index;
signals:
    void selectImg(int);
public slots:
    void addImg(Hobject *obj);
    void deleteImg(int index);
    int getListSize();
    void setLayout(QLayout *l);
    void deleteAllImg();
    void onClick();
};

#endif // IMGLIST_H
