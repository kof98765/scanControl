#ifndef POINTANALYZE_H
#define POINTANALYZE_H

#include <QDialog>
#include <QFileDialog>
#include "plot.h"

#include <QMouseEvent>
#include <QMenu>
#include <QFile>
#include <QIODevice>
#include <QTimer>
#include <QLinkedList>
#include <QSemaphore>
#include "qcustomplot.h"
#include <QVector>
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

    void timer_timeout();
public slots:
    void showData(double *x,double *y,int length);

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
    QCustomPlot *customPlot;
signals:
    void initDevice();
};

#endif // POINTANALYZE_H
