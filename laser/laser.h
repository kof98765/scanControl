#ifndef LASER_H
#define LASER_H

#include <QThread>

class laser : public QThread
{
    Q_OBJECT
public:
    explicit laser(QObject *parent = 0);

signals:

public slots:

};

#endif // LASER_H
