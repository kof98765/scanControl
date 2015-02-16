#ifndef mySettings_H
#define mySettings_H

#include <QDialog>
#include <QFileDialog>
#include <QSettings>
namespace Ui {
class mySettings;
}

class mySettings : public QDialog
{
    Q_OBJECT

public:
    explicit mySettings(QWidget *parent = 0);
    ~mySettings();

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
    Ui::mySettings *ui;
    QString filePath;
    QSettings set;
    QString *settings;
    QString *value;

signals:
    void netTest(QString msg);
    void updataSettings();
};

#endif // mySettings_H
