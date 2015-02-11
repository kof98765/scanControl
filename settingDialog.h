#ifndef DIALOGNETPARAM_H
#define DIALOGNETPARAM_H

#include <QDialog>
#include <QFileDialog>
#include <QSettings>
namespace Ui {
class DialogNetParam;
}

class DialogNetParam : public QDialog
{
    Q_OBJECT

public:
    explicit DialogNetParam(QWidget *parent = 0);
    ~DialogNetParam();

public slots:
    void recvData(char *);
    void flush_settings();

private slots:
    void on_Button_Yes_clicked();

    void on_open_clicked();

    void on_default_2_clicked();

    void on_sendButton_clicked();

    void on_resampleValue_currentIndexChanged(int index);

    void on_profileCount_valueChanged(int arg1);

    void on_profile_config_currentIndexChanged(int index);



    void on_idle_time_valueChanged(int arg1);

    void on_shutter_time_valueChanged(int arg1);

private:
    Ui::DialogNetParam *ui;
    QString filePath;
    QSettings set;
    QString *settings;
    QString *value;

signals:
    void netTest(QString msg);
};

#endif // DIALOGNETPARAM_H
