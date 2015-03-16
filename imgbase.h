#ifndef IMGBASE_H
#define IMGBASE_H

#include <QWidget>
#include <QTableWidget>
#include <QLabel>

namespace Ui {
class imgBase;
}

class imgBase : public QWidget
{
    Q_OBJECT

public:
    imgBase(QWidget *parent = 0);
    ~imgBase();
    QLabel *amp_view,*curv_view;

private:
    Ui::imgBase *ui;
};

#endif // IMGBASE_H
