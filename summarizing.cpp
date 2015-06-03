#include "summarizing.h"



summarizing::summarizing(QObject *parent) :
    QObject(parent)
{
    index=1;
    init();

}
void summarizing::init()
{


}
void summarizing::set_table(QTableWidget *t)
{
    table=t;

}
void summarizing::clear_table()
{
    int i,maxrow = table->rowCount();
	
    for(i=maxrow-1;i>=0;i--)
    {
        table->removeRow(i);
    }
    index=1;

}
void summarizing::add_row()
{
    table->setRowCount(index++);
    QTableWidgetItem *item=new QTableWidgetItem("OK");
    item->setTextColor(QColor("green"));
    item->setTextAlignment(Qt::AlignCenter);
    table->setItem(table->rowCount()-1,0,item);

    init();
}
void summarizing::calculateRepeatability(int column1,int column2)
{
    QStringList itemList;
    QMap<QString,double> maxList;
    QMap<QString,double> minList;
    for(int i=0;i<table->rowCount();i++)
    {
        QString tmp=table->item(i,column1)->text();
        if(!itemList.contains(tmp))
        {

            maxList.insert(tmp,table->item(i,column2)->text().toDouble());
            minList.insert(tmp,table->item(i,column2)->text().toDouble());
            itemList.append(tmp);
        }
        else
        {
            double value=table->item(i,column2)->text().toDouble();
            if(value>maxList.value(tmp))
                maxList.insert(tmp,value);
            if(value<minList.value(tmp))
                minList.insert(tmp,value);

        }

    }
    emit reportRepeatability(minList,maxList);
}
void summarizing::add_item(int type, QString str)
{

    QTableWidgetItem *item;


    item=new QTableWidgetItem(str);
    if(str=="NG")
        item->setTextColor(QColor("red"));
    table->setItem(table->rowCount()-1,type,item);
    item->setTextAlignment(Qt::AlignCenter);





}
void summarizing::to_excel()
{


    Record rec;
    QString str=QFileDialog::getSaveFileName(0,"save",".","xls",0,0);
    QFileInfo file(str);


    rec.set_Path(file.absolutePath());
    qDebug()<<file.absolutePath();
    qDebug()<<file.fileName();
    if(str.isEmpty())
    {
        return;
    }
    int tableR = table->rowCount();
    int tableC = table->columnCount();

    QList<QString> list;
        //获取表头写做第一行
        for (int i=0; i<tableC; i++)
        {
            if ( table->horizontalHeaderItem(i) != NULL )
            {
                list<<table->horizontalHeaderItem(i)->text();
            }
        }
    rec.init_excel(file.fileName(),list);
        //写数据
        for (int i=0; i<tableR; i++)
        {
            for (int j=0; j<tableC; j++)
            {
                if ( table->item(i,j) != NULL )
                {
                   // this->SetCellData(i+2,j+1,table->item(i,j)->text());
                    rec.add_record(i+2,j+1,table->item(i,j)->text());
                }
            }
        }

    rec.save_excel();




}
