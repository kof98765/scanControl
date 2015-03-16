#ifndef IMGVIEW_H
#define IMGVIEW_H

#include <QWidget>
#include <QDialog>
#include <QFrame>
#include <QGraphicsView>
#include <QDebug>
#include <QDir>
#include <QDirIterator>
#include <QPixmap>
#include <QFileDialog>
#include <QLabel>
#include <QtMath>
#include <QTime>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QLayout>
#include <QSizeGrip>
#include <QImage>
#include "HalconCpp.h"
using namespace Halcon;

namespace Ui {
class imgView;
}

class imgView : public QDialog
{
    Q_OBJECT

public:
    imgView(QDialog *parent = 0);
    ~imgView();
    void searchFile(QString path);

private:
    Ui::imgView *ui;

    QList<HTuple> handle1List,handle2List;
    QString path;
    QGridLayout *amp_grid,*curv_grid;
    QList<QLabel *> labelList;

    int index;
    void HimgToQimage(Hobject *img);
public slots:
    void display_img(Hobject img1,Hobject img2);
    void display_imgs(Hobject img1,Hobject img2);
    void clean();
signals:
    void Error(QString str);
};

#endif
