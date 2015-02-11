#include "record.h"

Record::Record(QObject *parent) :
    QObject(parent)
{
    cell      =NULL;
    worksheet =NULL;
    worksheets=NULL;
    workbook  =NULL;
    workbooks =NULL;
    excel     =NULL;
    //CoInitialize(NULL);
    OleInitialize(0);
    //设置文件保存目录为当前程序目录
    path=QDir::toNativeSeparators(QCoreApplication::applicationDirPath()+"/");



}
Record::~Record()
{
    //CoUninitialize();
    OleUninitialize();
    delete cell;
    delete worksheet;
    delete worksheets;
    delete workbook;
    delete workbooks;
    delete excel;

    qDebug()<<"exit";

}
/*
    函数名:init_excel
    参数:name为EXCEL文件名,list为EXCEL文件的表头
    作用:
    初始化EXCEL文件,如果没有,则创建,有则打开/
*/
void Record::init_excel(QString name,QList<QString> list)
{
     fileName=name;

     excel = new QAxObject("Excel.Application");
     //excel->setControl("Excel.Application"); //连接Excel控件
     excel->setProperty("Visible", false);   //显示窗体
     //excel->setProperty("Caption", tr("手机数据记录"));
     excel->setProperty("DisplayAlerts", false); //不显示任何警告信息。如果为true那么在关闭是会出现类似“文件已修改，是否保存”的提示
     workbooks = excel->querySubObject("WorkBooks");     //获取工作簿集合


     if(!QFile::exists(path+fileName+".xlsx") &!QFile::exists(path+fileName+".xls"))
     {
         creat_excel(list);
         qDebug()<<"creat"<<path<<fileName<<".xls";
     }
     else
     {
          workbooks->dynamicCall("Open(QString)", path+fileName);  //如果是阅读或者修改已经存在的excel文件，调用open函数
          qDebug()<<"open";
          workbook = excel->querySubObject("ActiveWorkBook");
          worksheets = workbook->querySubObject("Sheets");         //获取工作表集合
          worksheet = worksheets->querySubObject("Item(int)",1);
     }

}
/*
    设置文件保存目录
*/
void Record::set_Path(QString str)
{
    path=QDir::toNativeSeparators(str);
}
/*
    函数名:creat_excel
    参数:list为文件的表头
    作用:
    创建EXCEL文件
*/
void Record::creat_excel(QList<QString> list)
{

    workbooks->dynamicCall("Add"); //新建一个工作簿
    workbook = excel->querySubObject("ActiveWorkBook"); //获取当前工作簿

    worksheets = workbook->querySubObject("Sheets");         //获取工作表集合
    worksheet = worksheets->querySubObject("Item(int)",1);   //获取工作表集合的工作表-youmo
    worksheet->setProperty("Name","样品数据");
            //删除添加后多余的两项



    for(int i=0;i<list.size();i++)
    {
        cell = worksheet->querySubObject("Cells(int,int)", 1, i+1);
        cell->setProperty("Value",list.at(i));
    }

}
void Record::add_record(int row,int column,QString str)
{

    QString tmp;
    record_list.push_front(tmp.append("%1:%2:%3").arg(row).arg(column).arg(str));

}
void Record::write_record(int row,int column,QString str)
{

    cell=worksheet->querySubObject("Cells(int,int)",row+1,column);
    cell->setProperty("Value",str);

}
void Record::write_excel()
{

    QString tmp=record_list.takeLast();
    int row=tmp.mid(0,tmp.indexOf(":")).toInt();
    tmp=tmp.mid(tmp.indexOf(":")+1);

    int column=tmp.mid(0,tmp.indexOf(":")).toInt();
    tmp=tmp.mid(tmp.indexOf(":")+1);

    write_record(row,column,tmp);
}

void Record::save_excel()
{


    while(record_list.size())
    {
        write_excel();

    }
    workbook->dynamicCall("SaveAs(const QString&)",path+fileName);
    workbook->dynamicCall("Close()"); //关闭工作簿
    excel->dynamicCall("Quit()");     //关闭excel

    qDebug()<<"save finish";
}

