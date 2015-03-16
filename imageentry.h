#ifndef IMAGEENTRY_H
#define IMAGEENTRY_H

#include <QDialog>

namespace Ui {
class imageEntry;
}

class imageEntry : public QDialog
{
    Q_OBJECT

public:
    explicit imageEntry(QWidget *parent = 0);
    ~imageEntry();

private slots:
    void on_imgRegister_clicked();

    void on_takeSet_clicked();

    void on_cameraSet_clicked();

    void on_triggerSet_clicked();

    void on_flashSet_clicked();

    void on_lightSet_clicked();

    void on_extendLightSet_clicked();

    void on_save_clicked();

private:
    Ui::imageEntry *ui;
};

#endif // IMAGEENTRY_H
