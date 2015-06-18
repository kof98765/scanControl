#ifndef REPEATABILITYDIALOG_H
#define REPEATABILITYDIALOG_H

#include <QDialog>
#include <QMap>
#include "summarizing.h"
namespace Ui {
class repeatabilityDialog;
}

class repeatabilityDialog : public QDialog
{
    Q_OBJECT

public:
    explicit repeatabilityDialog(QWidget *parent = 0);
    ~repeatabilityDialog();

private:
    Ui::repeatabilityDialog *ui;
    summarizing *sum;
public slots:
    void recvRepeatability(QMap<QString,double>,QMap<QString,double>);
signals:
    void flush();
private slots:
    void on_excel_clicked();

};

#endif // REPEATABILITYDIALOG_H
