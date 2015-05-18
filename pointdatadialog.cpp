#include "pointdatadialog.h"
#include "ui_pointdatadialog.h"

pointDataDialog::pointDataDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pointDataDialog)
{
    ui->setupUi(this);
}

pointDataDialog::~pointDataDialog()
{
    delete ui;
}

void pointDataDialog::on_roiColor_clicked()
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
float pointDataDialog::convertPoint(float num,int xy)
{
    switch(xy)
    {
        case 0:
        num=num/0.02;
        break;
    case 1:
        num=num/0.1355;
        break;
    }
    return num;
}
void pointDataDialog::on_loadPoint_clicked()
{
    QString filePath=QFileDialog::getOpenFileName(this,QStringLiteral("点位文件"),".","txt (*.txt)");
    if(filePath.isEmpty())
        return;
    QFile f(filePath);
    f.open(QFile::ReadOnly);
    QPoint p,p2;
    QTextStream txtInput(&f);
    QString buf;

    while(!txtInput.atEnd())
    {
        buf=txtInput.readLine();

        p.setX(convertPoint(buf.mid(0,buf.indexOf(",")).toFloat(),0));
        buf=buf.mid(buf.indexOf(",")+1,buf.length());

        if(ui->func->currentIndex()==2)
        {

            p.setY(convertPoint(buf.mid(0,buf.indexOf(",")).toFloat(),1));
            buf=buf.mid(buf.indexOf(",")+1,buf.length());

            p2.setX(convertPoint(buf.mid(0,buf.indexOf(",")).toFloat(),0));
            buf=buf.mid(buf.indexOf(",")+1,buf.length());

            p2.setY(convertPoint(buf.mid(0,buf.length()).toFloat(),1));

        }
        else
        {
            p.setY(convertPoint(buf.mid(0,buf.length()).toFloat(),1));
        }
        qDebug()<<"point"<<p;

        QMap<QString,QVariant> map,limit;
        map.insert("Row",p.y());
        map.insert("Column",p.x());

        map.insert("Length1",ui->roiSize->value());
        map.insert("Length2",ui->roiSize->value());
        map.insert("name",ui->roiName->text());
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
        case 2:
             map.insert("func",5);
             map.insert("Row2",p2.y());
             map.insert("Column2",p2.x());
             map.insert("Length3",ui->roiSize->value());
             map.insert("Length4",ui->roiSize->value());

            break;
        }

        map.insert("drawType",0);


        qDebug()<<ui->roiName->text();
         emit addRoi(map);

    }


    close();




}
