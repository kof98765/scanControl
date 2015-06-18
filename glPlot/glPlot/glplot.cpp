#include "glplot.h"
#include "ui_glplot.h"

glPlot::glPlot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::glPlot)
{
    ui->setupUi(this);

    widget=new GLWidget(this);
    widget->show();
}

glPlot::~glPlot()
{
    delete ui;
}
