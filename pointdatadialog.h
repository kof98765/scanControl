#ifndef POINTDATADIALOG_H
#define POINTDATADIALOG_H

#include <QDialog>
#include <QColorDialog>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

}
namespace Ui {
class pointDataDialog;
}

class pointDataDialog : public QDialog
{
    Q_OBJECT

public:
    pointDataDialog(QWidget *parent = 0);
    ~pointDataDialog();
    float convertPoint(float num,int xy);
private slots:
    void on_roiColor_clicked();

    void on_loadPoint_clicked();
    void getPoint();
    void loadLua(char *);
signals:
    void addRoi(QMap<QString,QVariant>);
private:
    Ui::pointDataDialog *ui;


    lua_State *l;
};

#endif // POINTDATADIALOG_H
