#ifndef POINTDATADIALOG_H
#define POINTDATADIALOG_H

#include <QDialog>
#include <QColorDialog>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
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
signals:
    void addRoi(QMap<QString,QVariant>);
private:
    Ui::pointDataDialog *ui;
};

#endif // POINTDATADIALOG_H
