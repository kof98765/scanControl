#ifndef SET_H
#define SET_H

#include <QDialog>

namespace Ui {
class SetDialog;
}
class SetDialog : public QDialog
{
    Q_OBJECT
public:
    SetDialog(QWidget *parent = 0);
private:
    Ui::SetDialog *ui;
    struct argSet{
        int minArea;
        int maxArea;
        int smoothWidth;
        int smoothHeight;
        int offset;
    }yomo,toumin,yuanfan;
signals:

private slots:
    void yomoValueChange();
    void touminValueChange();
    void yuanfanValueChange();

};

#endif // SET_H
