#ifndef CALCULATEGROUP_H
#define CALCULATEGROUP_H
#include <QList>
#include <QSettings>
class Roi{
public:
    QString name;
    double x;
    double y;
    double angle;
    double startX;
    double startY;
    double endX;
    double endY;
    double width;
    double height;
    unsigned int color;
    double size;
    double minValue;
    double maxValue;
    double limit;
    int index;
    int func;
    int team;
};
class calculateGroup
{
public:
    calculateGroup();
    calculateGroup(int);
    int teamNo;
    QMap<QString,Roi> roiList;
    QSettings set;

    QList<QString> calculateGroup::getRoiList();
};

#endif // CALCULATEGROUP_H
