#include "imglistview.h"
clickLabel::clickLabel(QLabel *parent) :
    QLabel(parent)
{
    installEventFilter(this);
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
void imgListView::setLayout(QLayout *l)
{
    layout=(QHBoxLayout *)l;

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
void imgListView::deleteImg(int index)
{
    close_window(winList.at(index));
    winList.removeAt(index);
    layout->removeWidget(labelList.at(index));
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
