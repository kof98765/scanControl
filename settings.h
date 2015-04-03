#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>
#include <QtCore/QCoreApplication>
class Roi
{
    Roi()
    {
        name="rect";
    }
public:
    QString name;
    double x;
    double y;
    double angle;
    double endX;
    double endY;
    double width;
    double height;
    unsigned int color;
    double size;
    double limit;
    int index;
    int func;
    int team;
};
class settings : public QObject
{
    Q_OBJECT
public:
    static settings * instance();

    QMap<QString,QVariant> teamList;
    QMap<QString,QVariant> roiList;
    void addRoi(Roi* r);
    void delRoi(QString);

private:
    settings();
    QSettings set;
    static settings * m_instance;
signals:

public slots:


};

#endif // SETTINGS_H
