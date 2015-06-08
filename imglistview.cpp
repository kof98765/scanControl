#include "imglistview.h"
clickLabel::clickLabel(QLabel *parent) :
    QLabel(parent)
{
    installEventFilter(this);
}
clickLabel::~clickLabel()
{

}
bool clickLabel::eventFilter(QObject *obj, QEvent *e)
{
    if(e->type()==QEvent::MouseButtonPress)
        emit click();

    return QLabel::eventFilter(obj,e);
}

imgListView::imgListView(QObject *parent) :
    QObject(parent)
{

}
void imgListView::setHBoxLayout(QLayout *l)
{
    layout=(QHBoxLayout *)l;
    l->setAlignment(Qt::AlignCenter);

}
void imgListView::setGridLayout(int w,int h,QGridLayout *l)
{
    l->setColumnMinimumWidth(w,h);
    layout=l;
     l->setAlignment(Qt::AlignCenter);
}
void imgListView::addImg(Hobject *obj)
{
    imgList.push_back(obj);
    clickLabel *l=new clickLabel;
    l->setFixedSize(50,50);
    connect(l,SIGNAL(click()),this,SLOT(onClick()));
    labelList.push_back(l);
    layout->addWidget(l);
    Hlong win,width,height;
    open_window(0,0,50,50,l->winId(),"visible","",&win);
    get_image_size(*obj,&width,&height);
    set_part(win,0,0,height,width);
    set_lut(win,"rainbow");
    winList.push_back(win);
    disp_obj(*obj,win);

}
void imgListView::addImg(QString path)
{
    Hobject *img=new Hobject;
    QTextCodec* gbk = QTextCodec::codecForName("GBK");
    //QTextCodec* utf8 = QTextCodec::codecForName("UTF-8");
    //编码器可以把QString转换为自己的编码：
    QByteArray ba = gbk->fromUnicode(path);
    char* c = ba.data();
    read_image(img,c);
    addImg(img);
}
void imgListView::deleteImg(int index)
{
    close_window(winList.at(index));
    winList.removeAt(index);
    layout->removeWidget(labelList.at(index));
    disconnect(labelList.at(index),SIGNAL(click()),this,SLOT(onClick()));
    labelList.at(index)->deleteLater();
    labelList.removeAt(index);
    imgList.removeAt(index);
    layout->update();
}
void imgListView::deleteAllImg()
{
    qDebug()<<getListSize();
    for(int i=getListSize();i>0;i--)
    {
        close_window(winList.at(i-1));
        winList.removeAt(i-1);
        layout->removeWidget(labelList.at(i-1));
        labelList.at(i-1)->deleteLater();
        labelList.removeAt(i-1);
        imgList.removeAt(i-1);
        layout->update();

    }
}
int imgListView::getListSize()
{
    return imgList.size();
}
void imgListView::onClick()
{

    if (clickLabel* label = dynamic_cast<clickLabel*>(sender())){
        int i=layout->indexOf(label);

        emit selectImg(i);

    }
}
