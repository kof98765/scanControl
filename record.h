#ifndef RECORD_H
#define RECORD_H

#include <QObject>
#include <QDebug>
#include <QAxObject>
#include <QDir>
#include <QCoreApplication>
#include <QTimer>
#include <QThread>
#include <QSemaphore>
#include <qt_windows.h>
#include <QProgressBar>

class Record : public QObject
{
    Q_OBJECT
public:
    explicit Record(QObject *parent = 0);
    ~Record();
    void init_excel(QString name,QList<QString> list);
    void write_record(int row,int column,QString str);

    void save_excel();
    void creat_excel(QList<QString> list);
    void set_Path(QString str);
    void add_record(int row,int column,QString str);
private:
    QString fileName;
    QString path;
    QAxObject *excel, *workbooks, *workbook, *worksheets, *worksheet;
    QAxObject *cell;
    QList<QString> record_list;




signals:

public slots:
    void write_excel();
};

#endif // RECORD_H
