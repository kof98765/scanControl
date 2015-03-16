#include "dialogimgparam.h"
#include "ui_dialogimgparam.h"
#include <QDebug>

DialogImgParam::DialogImgParam(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogImgParam)
{
    ui->setupUi(this);

    connect(ui->pushButton_Yes,SIGNAL(clicked()),this,SLOT(saveResult()));


    restore();

}

DialogImgParam::~DialogImgParam()
{
    delete ui;
}
void DialogImgParam::saveResult()
{
    /*
    float Line_Threshold_Low, Line_Threshold_High, Line_Mean_Dev,Line_Width_Sigama,Line_Length_Max,Line_Length_Min;
    float PointB_Dyn_Threshold, PointB_Mean_Width, PointB_Mean_Height, PointB_Area_Min,PointB_Area_Max;
    float PointW_Dyn_Threshold, PointW_Mean_Dev, PointW_Area_Mean,PointW_Area_Min,PointW_Area_Max;
    float PointF_Dyn_Threshold, PointF_Mean_Dev, PointF_Area_Deviation,PointF_Area_Min,PointF_Area_Max;
    float Dirt_f;
    float CurveW_Mean_Min;
    */
    set.setValue("Line_Threshold_Low",ui->Line_Low_Threshold->text().toFloat());
    set.setValue("Line_Threshold_High",ui->Line_High_Threshold->text().toFloat());
    set.setValue("Line_Mean_Dev", ui->Line_Mean_Dev->text().toFloat());
    set.setValue("Line_Width_Sigama",ui->Line_Width_Sigama->text().toFloat());
    set.setValue("Line_Length_Max",ui->Line_Length_Max->text().toFloat());
    set.setValue("Line_Length_Min",ui->Line_Length_Min->text().toFloat());
    set.setValue("PointB_Dyn_Threshold",ui->DyThresholdB_Offset->text().toFloat());
    set.setValue("PointB_Mean_Width",ui->MaskB_Width->text().toFloat());
    set.setValue("PointB_Mean_Height",ui->MaskB_Height->text().toFloat());
    set.setValue("PointB_Area_Min",ui->AreaB_Min->text().toFloat());
    set.setValue("PointB_Area_Max",ui->AreaB_Max->text().toFloat());

    set.setValue("PointW_Dyn_Threshold",ui->DyThresholdW_Offset->text().toFloat());
    set.setValue("PointW_Mean_Dev",ui->AreaW_MeanW_Dev->text().toFloat());
    //PointW_Area_Mean
    set.setValue("PointW_Area_Min",ui->AreaW_Min->text().toFloat());
    set.setValue("PointW_Area_Max",ui->AreaW_Max->text().toFloat());
    set.setValue("PointF_Dyn_Threshold",ui->DyF_Offset->text().toFloat());
    set.setValue("PointF_Mean_Dev",ui->AreaF_MeanDev->text().toFloat());
    set.setValue("PointF_Area_Deviation",ui->AreaF_Deviation->text().toFloat());
    set.setValue("PointF_Area_Min",ui->AreaF_Min->text().toFloat());
    set.setValue("PointF_Area_Max",ui->AreaF_Max->text().toFloat());
    //Dirt_f

    set.setValue("CurveW_Mean_Min",ui->MeanW_Min->text().toFloat());
    qDebug()<<"saved!";
    set.sync();
    accept();
}
/*
    恢复默认配置
*/
void DialogImgParam::setDefault()
{
    set.setValue("Line_Threshold_Low",7);
    set.setValue("Line_Threshold_High",10);
    set.setValue("Line_Mean_Dev", 15);
    set.setValue("Line_Width_Sigama",1.0);
    set.setValue("Line_Length_Max",300);
    set.setValue("Line_Length_Min",5);
    set.setValue("PointB_Dyn_Threshold",31);
    set.setValue("PointB_Mean_Width",17);
    set.setValue("PointB_Mean_Height",17);
    set.setValue("PointB_Area_Min",10);
    set.setValue("PointB_Area_Max",160);

    set.setValue("PointW_Dyn_Threshold",25);
    set.setValue("PointW_Mean_Dev",40);
    //PointW_Area_Mean
    set.setValue("PointW_Area_Min",10);
    set.setValue("PointW_Area_Max",160);
    set.setValue("PointF_Dyn_Threshold",31);
    set.setValue("PointF_Mean_Dev",15);
    set.setValue("PointF_Area_Deviation",5);
    set.setValue("PointF_Area_Min",2);
    set.setValue("PointF_Area_Max",50);
    //Dirt_f

    set.setValue("CurveW_Mean_Min",215);
    set.sync();
}
/*
   函数名：restore
   参数：无
   作用：
   把界面上的设置重置，可以把界面上的数值恢复为之前设定的值
*/
void DialogImgParam::restore()
{

    ui->Line_Low_Threshold->setValue(set.value("Line_Threshold_Low",7).toFloat());
    ui->Line_High_Threshold->setValue(set.value("Line_Threshold_High",10).toFloat());
    ui->Line_Mean_Dev->setValue(set.value("Line_Mean_Dev",15).toFloat());
    ui->Line_Width_Sigama->setValue(set.value("Line_Width_Sigama",1.0).toFloat());
    ui->Line_Length_Max->setValue(set.value("Line_Length_Max",300).toFloat());
    ui->Line_Length_Min->setValue(set.value("Line_Length_Min",15).toFloat());

    ui->DyThresholdB_Offset->setValue(set.value("PointB_Dyn_Threshold",31).toFloat());
    ui->MaskB_Width->setValue(set.value("PointB_Mean_Width",17).toFloat());
    ui->MaskB_Height->setValue(set.value("PointB_Mean_Height",17).toFloat());
    ui->AreaB_Min->setValue(set.value("PointB_Area_Min",10).toFloat());
    ui->AreaB_Max->setValue(set.value("PointB_Area_Max",160).toFloat());

    ui->DyThresholdW_Offset->setValue(set.value("PointW_Dyn_Threshold",25).toFloat());
    ui->AreaW_MeanW_Dev->setValue(set.value("PointW_Mean_Dev",40).toFloat());
    //PointW_Area_Mean
    ui->AreaW_Min->setValue(set.value("PointW_Area_Min",10).toFloat());
    ui->AreaW_Max->setValue(set.value("PointW_Area_Max",160).toFloat());

    ui->DyF_Offset->setValue(set.value("PointF_Dyn_Threshold",31).toFloat());
    ui->AreaF_MeanDev->setValue(set.value("PointF_Mean_Dev",15).toFloat());
    ui->AreaF_Deviation->setValue(set.value("PointF_Area_Deviation",5).toFloat());
    ui->AreaF_Min->setValue(set.value("PointF_Area_Min",2).toFloat());
    ui->AreaF_Max->setValue(set.value("PointF_Area_Max",50).toFloat());

    //Dirt_f

    ui->MeanW_Min->setValue(set.value("CurveW_Mean_Min",215).toFloat());

}


/*
   函数名：on_restoreButton
   参数：无
   作用：
   取消按钮，取消并且回复到之前的状态
*/
void DialogImgParam::on_pushButton_Cancel_clicked()
{
    restore();
    close();
}


/*
   函数名：on_restoreButton
   参数：无
   作用：
   恢复默认按钮，恢复成程序初始的数值
*/
void DialogImgParam::on_restoreButton_clicked()
{
    setDefault();
    restore();

}
