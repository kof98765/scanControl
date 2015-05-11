#include "calculategroup.h"

calculateGroup::calculateGroup()
{

}
calculateGroup::calculateGroup(int no)
{
    teamNo=no;
    QList<QString> data=set.value("dataList").toMap().value(QString::number(no)).toList();

    for(int i=0;i<data.size();i++)
    {
        Roi roi;
        roi.angle=set.value("team/"+data.at(i)).toMap().value("Phi",0).toDouble();
        roi.color=set.value("team/"+data.at(i)).toMap().value("color",0).toInt();
        roi.startX=set.value("team/"+data.at(i)).toMap().value("Row",0).toDouble();
        roi.startY=set.value("team/"+data.at(i)).toMap().value("Column",0).toDouble();
        roi.endX=set.value("team/"+data.at(i)).toMap().value("Row2",0).toDouble();
        roi.endY=set.value("team/"+data.at(i)).toMap().value("Column2",0).toDouble();
        roi.func=set.value("team/"+data.at(i)).toMap().value("func",0).toInt();
        roi.height=set.value("team/"+data.at(i)).toMap().value("Length1",50).toDouble();
        roi.width=set.value("team/"+data.at(i)).toMap().value("Length2",50).toDouble();
        roi.index=set.value("team/"+data.at(i)).toMap().value("index",0).toInt();
        roi.limit=set.value("team/"+data.at(i)).toMap().value("limit",0).toDouble();
        roi.minValue=set.value("team/"+data.at(i)).toMap().value("min",0).toDouble();
        roi.maxValue=set.value("team/"+data.at(i)).toMap().value("max",0).toDouble();
        roi.name=data.at(i);
        roi.size=set.value("team/"+data.at(i)).toMap().value("size").toDouble();
        roi.team=no;
        roi.x=set.value("team/"+data.at(i)).toMap().value("Row").toDouble();
        roi.y=set.value("team/"+data.at(i)).toMap().value("Column").toDouble();
        roiList.insert(data.at(i),roi);

    }
}
QList<QString> calculateGroup::getRoiList()
{
   return roiList.keys();
}
