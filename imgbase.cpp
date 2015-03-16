#include "imgbase.h"
#include "ui_imgbase.h"

imgBase::imgBase(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::imgBase)
{
    ui->setupUi(this);
    amp_view=ui->amp_view;
    curv_view=ui->curv_view;
}

imgBase::~imgBase()
{
    delete ui;
}
