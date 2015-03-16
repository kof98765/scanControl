#ifndef DIALOGCAMERALIGHT_H
#define DIALOGCAMERALIGHT_H

#include <QDialog>


namespace Ui {
class DialogCameraLight;
}

class DialogCameraLight : public QDialog
{
    Q_OBJECT

public:
    explicit DialogCameraLight(QWidget *parent = 0);
    ~DialogCameraLight();

private:
    Ui::DialogCameraLight *ui;
public slots:

signals:


};

#endif // DIALOGCAMERALIGHT_H
