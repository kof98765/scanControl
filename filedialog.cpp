#include "filedialog.h"
#include "ui_filedialog.h"
#include <QDebug>


fileDialog::fileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fileDialog)
{
    ui->setupUi(this);
    connect(ui->rawimg_button,SIGNAL(clicked()),this,SLOT(openImgFiles()));
    connect(ui->fouimg_button,SIGNAL(clicked()),this,SLOT(openImgFiles()));
    connect(ui->quimg_button,SIGNAL(clicked()),this,SLOT(openImgFiles()));
    connect(ui->cancleButton,SIGNAL(clicked()),this,SLOT(close()));
    connect(ui->okButton,SIGNAL(clicked()),this,SLOT(ok()));



}

fileDialog::~fileDialog()
{
    delete ui;
}
void fileDialog::openImgFiles()
{
    QString path;
    ui->okButton->setEnabled(false);
    if(list.size()>=3)
        list.clear();

    if (QPushButton* btn = dynamic_cast<QPushButton*>(sender())){

            if(btn==ui->rawimg_button)
            {
                path=QFileDialog::getOpenFileName(this,QStringLiteral("打开图像"),".",QStringLiteral("原始图像")+(" (*.bmp *.jpg *.jpeg)\n" "otherFile (*.*)"));
                if(!path.isEmpty())
                {
                    list.insert(0,path);
                    ui->rawimg_edit->setText(list.at(0));
                }
            }
            if(btn==ui->fouimg_button)
            {
                path=QFileDialog::getOpenFileName(this,QStringLiteral("打开图像"),".",QStringLiteral("原始图像")+(" (*.bmp *.jpg *.jpeg)\n" "otherFile (*.*)"));
                if(!path.isEmpty())
                {
                    list.insert(1,path);
                    ui->fouimg_edit->setText(list.at(1));
                }
            }
            if(btn==ui->quimg_button)
            {
                path=QFileDialog::getOpenFileName(this,QStringLiteral("打开图像"),".",QStringLiteral("原始图像")+(" (*.bmp *.jpg *.jpeg)\n" "otherFile (*.*)"));
                if(!path.isEmpty())
                {
                    list.insert(2,path);
                    ui->quimg_edit->setText(list.at(2));
                }
            }

        }
    if(list.size()==3)
        ui->okButton->setEnabled(true);



}
void fileDialog::ok()
{
    ui->okButton->setEnabled(true);
    emit setFileList(list);
    close();
}
/*
    函数：textChange
    参数：str为接收到的字符串
    作用：
    多个信号的响应
*/
void fileDialog::textChange(QString str)
{
    /*
    if (QLineEdit* edit = dynamic_cast<QLineEdit*>(sender())){
        if(edit==ui->rawimg_edit)
            list.insert(0,str);
        if(edit==ui->fouimg_edit)
            list.insert(1,str);
        if(edit==ui->quimg_edit)
            list.insert(2,str);
    }
    emit setFileList(list);
*/
}
