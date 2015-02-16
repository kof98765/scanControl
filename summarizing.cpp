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
    qDebug()<<"rowcount"<<maxrow;
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
void summarizing::add_item(int type, QString str)
{

    QTableWidgetItem *item;


    item=new QTableWidgetItem(str);

    if(str=="NG")
        item->setTextColor(QColor("red"));
    //item2=new QTableWidgetItem("NG");
    table->setItem(table->rowCount()-1,type,item);
   // qDebug()<<table->rowCount()-1<<type<<str;
  //  table->setItem(table->rowCount()-1,0,item2);
    item->setTextAlignment(Qt::AlignCenter);
   // item2->setTextAlignment(Qt::AlignCenter);




}
void summarizing::to_excel()
{


    Record rec;
    QString str=QFileDialog::getSaveFileName(0,"save",".","",0,0);
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
