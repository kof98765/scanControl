#ifndef ROBOT_H
#define ROBOT_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QThread>
#include <QDebug>
#include <QMessageBox>
#include "process.h"
class Robot : public QObject
{
    Q_OBJECT
public:
    Robot(QObject *parent = 0);


public slots:
    void tcpDate();
    void stopMove();
    void makeAMove();
    void detectNG();
    void newConnect();
    void initSocked(QString ip,int tcpport);
    void displayError(QAbstractSocket::SocketError socketError);
private:
    QByteArray *tmp;
    int port;
    QString serverIp;
    QTcpSocket *tcpClient;
    QByteArray data;
    bool isRunning;
    QTcpServer *server;

signals:
    void takeAPhoto();
    void netError(QString error);



};

#endif // ROBOT_H
