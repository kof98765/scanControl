#include "setdialog.h"
#include <QDebug>
Set::Set(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetDialog)
{
    setupUi(this);
    connect(okButton,SIGNAL(clicked()),this,SLOT(yomoValueChange()));
    connect(cancelButton,SIGNAL(clicked()),this,SLOT(close()));

}
void Set::yomoValueChange()
{


    yomo.maxArea=YouMo_AreaBig->value();

    yomo.minArea=YouMo_AreaSmall->value();

    yomo.offset=YouMo_offSet->value();

    yomo.smoothHeight=YouMo_smoothHeight->value();

    yomo.smoothWidth=YouMo_smoothWidth->value();
    close();

}
void Set::touminValueChange()
{
    toumin.maxArea=YouMo_AreaBig_2->value();
    toumin.minArea=YouMo_AreaSmall_2->value();
    toumin.offset=YouMo_offSet_2->value();
    toumin.smoothHeight=YouMo_smoothHeight_2->value();
    toumin.smoothWidth=YouMo_smoothWidth_2->value();

}

void Set::yuanfanValueChange()
{
    yuanfan.maxArea=YouMo_AreaBig_3->value();
    yuanfan.minArea=YouMo_AreaSmall_3->value();
    yuanfan.offset=YouMo_offSet_3->value();
    yuanfan.smoothHeight=YouMo_smoothHeight_3->value();
    yuanfan.smoothWidth=YouMo_smoothWidth_3->value();

}
