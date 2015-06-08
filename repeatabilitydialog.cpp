#include "repeatabilitydialog.h"
#include "ui_repeatabilitydialog.h"

repeatabilityDialog::repeatabilityDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::repeatabilityDialog)
{
    ui->setupUi(this);
    sum=new summarizing;
    sum->set_table(ui->tableWidget);
}

repeatabilityDialog::~repeatabilityDialog()
{
    delete sum;
    delete ui;
}
void repeatabilityDialog::recvRepeatability(QMap<QString,double> minList,QMap<QString,double> maxList)
{
    sum->clear_table();
    for(int i=0;i<minList.keys().size();i++)
    {
        QString key=minList.keys().at(i);
        sum->add_row();
        sum->add_item(0,key);
        sum->add_item(1,QString::number(minList.value(key)));
        sum->add_item(2,QString::number(maxList.value(key)));
        sum->add_item(3,QString::number(maxList.value(key)-minList.value(key)));

    }
}

void repeatabilityDialog::on_excel_clicked()
{
    sum->to_excel();
}
