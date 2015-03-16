#include "imgView.h"
#include "ui_imgView.h"


imgView::imgView(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::imgView)
{
    ui->setupUi(this);
    //setWindowFlags(Qt::FramelessWindowHint);
    this->setWindowState(Qt::WindowMaximized);
    amp_grid=new QGridLayout;
    curv_grid=new QGridLayout;
    amp_grid->setColumnMinimumWidth(3,100);
    curv_grid->setColumnMinimumWidth(3,100);
    ui->amp_area_widget->setLayout(amp_grid);
    ui->curv_area_widget->setLayout(curv_grid);

}

imgView::~imgView()
{
    delete ui;

}
void imgView::display_img(Hobject img1,Hobject img2)
{
     QLabel *lab=new QLabel(ui->amp_area_widget);
     QLabel *lab2=new QLabel(ui->curv_area_widget);
     lab->setFixedSize(320,240);
     lab2->setFixedSize(320,240);

     HTuple handle1,handle2;
    open_window(0,0,320,240,lab->winId(),"visible","",&handle1);

     set_part(handle1,0,0,1234-1,1264-1);
     disp_obj(img1,handle1);

     open_window(0,0,320,240,lab2->winId(),"visible","",&handle2);

     set_part(handle2,0,0,1234-1,1264-1);
     disp_obj(img2,handle2);

     handle1List.append(handle1);
     handle2List.append(handle2);

     amp_grid->addWidget(lab);
     curv_grid->addWidget(lab2);
     lab->show();
     lab2->show();
}
void imgView::clean()
{
    for(int i=0;i<handle1List.size();i++)
    {
        close_window(handle1List.at(i));
    }
    for(int i=0;i<handle2List.size();i++)
    {
        close_window(handle2List.at(i));
    }
    for(int i=0;i<labelList.size();i++)
    {
        delete labelList.at(i);
    }

}
void imgView::display_imgs(Hobject imgs1,Hobject imgs2)
{
    Hobject img1,img2;
    Hlong num1,num2;
    count_obj(imgs1,&num1);
    count_obj(imgs2,&num2);
    if(num1!=num2)
    {
        emit Error("imgs1 and imgs2 error!");
        return;
    }
    for(int i=0;i<num1;i++)
    {
        select_obj(imgs1,&img1,i);
        select_obj(imgs2,&img2,i);
        display_img(img1,img2);
    }
}

void imgView::HimgToQimage(Hobject *img)
{
    /*
    QImage*   qimg;
    HTuple     htChannels;
    char cType[MAX_STRING];
    Hlong    width,height;
    width=height=0;
    //转换图像格式
    convert_image_type(img,&img,"byte");
    count_channels(img,&htChannels);
    if(htChannel[0].I()==1)
    {
        unsinged char* ptr;
        get_image_pointer1(img,(Hlong*)&ptr,cType,&width,&height);
        qimg=new QImage(QSize(width,height),QImage::Format_Indexed8);
        pImage=cvCreateImage(cvSize(width,height),IPL_DEPTH_8U,1);
        for(int i=0;i<height;i++)
        {
            memcpy(qimg->bits()+qimg->width()*i,ptr+width*i,width);
        }
        qimg = qimg.rgbSwapped();
    }
    if(htChannels[0].I()==3)
    {
        unsigned char *ptrRed , *ptrGreen , *ptrBlue;
        ptrRed=ptrGreen=ptrBlue=NULL;
        get_image_pointer3(img,(Hlong*)&ptrRed,(Hlong*)&ptrGreen,(Hlong*)&ptrBlue,cType,&width,&height);
        QImage *red,*blue,*green;
        red=new QImage(QSize(width,height),QImage::Format_Indexed8);
        blue=new QImage(QSize(width,height),QImage::Format_Indexed8);
        green=new QImage(QSize(width,height),QImage::Format_Indexed8);
        qimg=new QImage(qSize(width,height),QImage::Format_RGB888);

    for(int i=0;i<height;i++)
    {
    memcpy(red->bits()+red->width()*i , ptrRed+width*i , width);
    memcpy(green->bits()+green->width()*i , ptrGreen+width*i , width);
    memcpy(blue->bits()+blue->width()*i , ptrBlue+width*i , width);
    }

    cvReleaseImage(&pImageRed);
    cvReleaseImage(&pImageGreen);
    cvReleaseImage(&pImageBlue);
    }
    return pImage;
    }
    */
}
