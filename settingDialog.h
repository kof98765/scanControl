#ifndef mySettings_H
#define mySettings_H

#include <QDialog>
#include <QFileDialog>
#include <QSettings>
#include <QDebug>
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
    void debugMessage(QString str);
private slots:
    void on_Button_Yes_clicked();

    void on_open_clicked();

    void on_default_2_clicked();

    void on_sendButton_clicked();

    void on_resampleValue_currentIndexChanged(int index);

    void on_profileCount_valueChanged(int arg1);




    void on_connecct_clicked();

    void on_exposure_currentIndexChanged(int index);



    void on_testValue_valueChanged(double arg1);

    void on_trigger_currentIndexChanged(int index);

private:
    Ui::mySettings *ui;
    QString filePath;
    QSettings set;
    QString *settings;
    QString *value;

signals:
    void netTest(QString msg);
    void updataSettings();
    void selectDevice(int index);
    void postExposeTime(int s,int i);
    void setExternTrigger(int index);
};

#endif // mySettings_H
