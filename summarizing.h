#ifndef SUMMARIZING_H
#define SUMMARIZING_H

#include <QObject>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QFileDialog>
#include <QDebug>
#include "record.h"
#include <QProgressBar>


class summarizing : public QObject
{
    Q_OBJECT
public:
    explicit summarizing(QObject *parent = 0);
private:
    int white_block;
    int black_block;
    int white_line;
    int black_line;
    int index;
    QTableWidget *table;


signals:
    void write_excel(int row,int count,QString);
    void Error(QString str);
    void reportRepeatability(QMap<QString,double>,QMap<QString,double>);

public slots:
    void add_item(int type,QString str);
    void set_table(QTableWidget *t);
    void calculateRepeatability(int keyColumn,int valueColumn );
    void add_row();
    void init();
    void clear_table();
    void to_excel();
};

#endif // SUMMARIZING_H
