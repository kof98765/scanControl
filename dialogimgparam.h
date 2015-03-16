#ifndef DIALOGIMGPARAM_H
#define DIALOGIMGPARAM_H

#include <QDialog>
#include <QSettings>

namespace Ui {
class DialogImgParam;
}

class DialogImgParam : public QDialog
{
    Q_OBJECT

public:
    explicit DialogImgParam(QWidget *parent = 0);
    ~DialogImgParam();
    void restore();
    void setDefault();

private slots:
    void saveResult();
    void on_pushButton_Cancel_clicked();
    void on_restoreButton_clicked();

private:
    Ui::DialogImgParam *ui;
    QSettings set;

};

#endif // DIALOGIMGPARAM_H
