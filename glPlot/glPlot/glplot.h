#ifndef GLPLOT_H
#define GLPLOT_H

#include <QWidget>
#include "glwidget.h"
namespace Ui {
class glPlot;
}

class glPlot : public QWidget
{
    Q_OBJECT

public:
    explicit glPlot(QWidget *parent = 0);
    ~glPlot();

private:
    Ui::glPlot *ui;
    GLWidget *widget;
};

#endif // GLPLOT_H
