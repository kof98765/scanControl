#include "settings.h"

settings::settings() :
    QObject(qApp)
{
    teamList=set.value("dataList").toMap();
    roiList=set.value("roiList").toMap();

}
settings * settings::m_instance = 0;
settings * settings::instance()
{
    static QMutex mutex;
    if (!m_instance) {
        QMutexLocker locker(&mutex);
        if (!m_instance)
            m_instance = new settings;
    }

    return m_instance;
}
void settings::addRoi(Roi* r)
{
    QStringList str;
    str<<QString::number(r->color);
    if(r->func==2|r->func==3)
    {

        str<<QString::number(r->x);
        str<<QString::number(r->y);
        str<<QString::number(r->angle);
        str<<QString::number(r->width);
        str<<QString::number(r->height);

    }
    else
    {

        //roiList[1-5]
        str<<QString::number(r->x);
        str<<QString::number(r->y);
        str<<QString::number(r->endX);
        str<<QString::number(r->endY);
        str<<QString::number(0);
    }


   //Ð´ÈëÅäÖÃÎÄ¼þ
    //roiList[6-9]
    str<<QString::number(r->team);
    str<<QString::number(r->func);
    str<<QString::number(r->index);
    str<<QString::number(r->limit);
    roiList.insert(r->name,QVariant(str));

    QString teamNum=QString::number(r->team);
    QStringList data;


    data=teamList.value(teamNum).toStringList();
    data<<r->name;
    teamList.insert(teamNum,data);

    set.setValue("dataList",teamList);
    set.setValue("roiList",roiList);
    set.sync();

}
void settings::delRoi(QString name)
{

    for(int i=0;i<teamList.size();i++)
    {
        for(int j=0;j<teamList.keys().size();j++)
        {

        }
    }

}
