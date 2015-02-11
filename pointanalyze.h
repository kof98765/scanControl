#ifndef POINTANALYZE_H
#define POINTANALYZE_H

#include <QDialog>
#include <QFileDialog>
#include "plot.h"
#include "settings.h"
#include <QMouseEvent>
#include <QMenu>
#include <QFile>
#include <QIODevice>
#include <QTimer>
#include <QLinkedList>
#include <QSemaphore>
#define FRAME_LENGTH 1280
namespace Ui {
class pointAnalyze;
}

class pointAnalyze : public QDialog
{
    Q_OBJECT

public:
    explicit pointAnalyze(QWidget *parent = 0);
    ~pointAnalyze();
    void readPointCloudDate(QString str);
protected:

private slots:
    void on_loadButton_clicked();

    void on_nextFrame_clicked();


    void on_preFrame_clicked();
    void on_reset_clicked();

    void on_numFrame_valueChanged(int arg1);

    void on_pushButton_clicked();
    void timer_timeout();

public:
    void readFrame();
private:
    Ui::pointAnalyze *ui;
    QString filePath;
    Plot *plot;
    qint64 offset;
    qint64 first_offset;
    int index;
    int status;
    bool isRunning;
    qint64 maxIndex;
    QByteArray *buf;
    QList<double> data;
    QSemaphore sem;
    QMutex mux;
    QTimer *timer;
signals:
    void initDevice();
};

#endif // POINTANALYZE_H
