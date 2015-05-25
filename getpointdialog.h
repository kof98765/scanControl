#ifndef GETPOINTDIALOG_H
#define GETPOINTDIALOG_H

#include <QDialog>
#include <QMap>
#include <QVariant>
#include <QColorDialog>
#include <QDebug>
namespace Ui {
class getPointDialog;
}

class getPointDialog : public QDialog
{
    Q_OBJECT

public:
     getPointDialog(QWidget *parent = 0);
    ~getPointDialog();

private slots:
    void on_creat_clicked();
    void on_roiColor_clicked();

signals:
    void addRoi(QMap<QString,QVariant>);
private:
    Ui::getPointDialog *ui;
};

#endif // GETPOINTDIALOG_H
