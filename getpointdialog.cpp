#include "getpointdialog.h"
#include "ui_getpointdialog.h"
//qRegisterMetaType<QMap<QString,QVariant>> ("QMap<QString,QVariant>");
getPointDialog::getPointDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::getPointDialog)
{

    ui->setupUi(this);
    qDebug()<<ui->groupBox->children();
}

getPointDialog::~getPointDialog()
{
    delete ui;
}

void getPointDialog::on_creat_clicked()
{
    QMap<QString,QVariant> map;
    double x=0,y=0;
    x+=ui->offsetX->value()/ui->scaleX->value();
    y+=ui->offsetY->value()/ui->scaleY->value();
    for(int i=0;i<ui->pointCount->value();i++)
    {
        if(i!=0)
        switch(ui->comboBox->currentIndex())
        {

        case 0:

            y-=(ui->spaceY->value()/ui->scaleY->value());

            break;
        case 1:

            y+=(ui->spaceY->value()/ui->scaleY->value());
            break;
        case 2:

            x-=(ui->spaceX->value()/ui->scaleX->value());
            break;
        case 3:

            x+=(ui->spaceX->value()/ui->scaleX->value());
            break;
        case 4:


            break;
        case 5:
            break;
        }
        map.insert("Row",y);
        map.insert("Column",x);

        map.insert("Length1",5);
        map.insert("Length2",5);

        map.insert("color",ui->roiColor->palette().background().color().rgb());
        map.insert("team",ui->roiTeam->currentIndex());
        switch(ui->func->currentIndex())
        {
        case 0:
            map.insert("func",3);
            break;
        case 1:
            map.insert("func",4);
            break;

        }

        map.insert("drawType",0);

        emit addRoi(map);

    }

    close();
}


void getPointDialog::on_roiColor_clicked()
{
    QColor color=QColorDialog::getColor();
    if(color.isValid()){
        int r,g,b;
        color.getRgb(&r,&g,&b);
        QString str;
        str=QString("background-color: rgb(%1,%2,%3)").arg(r).arg(g).arg(b);
        ui->roiColor->setStyleSheet(str.toUtf8().data());
        //QPalette pal=ui->roiColor->palette();
        //pal.setColor(QPalette::Active,QPalette::Button, color);
        //ui->roiColor->setPalette(pal);
        qDebug()<<color.rgb();
        qDebug()<<((color.rgb()&(0xff<<16))>>16)<<((color.rgb()&(0xff<<8))>>8)<<(color.rgb()&(0xff));
        ui->roiColor->update();
    }
}
