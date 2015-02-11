#include "robot.h"

Robot::Robot(QObject *parent) :
    QObject(parent)
{
     tcpClient=new QTcpSocket;
     server=new QTcpServer;
}
/*
    函数名:initSocket
    参数:ip为远程服务器的地址,tcpport为远程服务器端口或者本地服务端口
    作用:
    初始化网络,有两种模式,服务器模式或者客户端模式,需要重新编译才可生效
*/
void Robot::initSocked(QString ip,int tcpport)
{
    serverIp=ip;
    port=tcpport;
#ifdef CLIENT
    tcpClient->abort();

    connect(tcpClient, SIGNAL(error(QAbstractSocket::SocketError)),
               this, SLOT(displayError(QAbstractSocket::SocketError)));

    connect(tcpClient,SIGNAL(readyRead()),this,SLOT(tcpDate()));

   tcpClient->connectToHost(serverIp,port);
    //tcpClient->write("Ready",6);
#else

    server->listen(QHostAddress::LocalHost,port);
    connect(server,SIGNAL(acceptError(QAbstractSocket::SocketError)),this,SLOT(displayError(QAbstractSocket::SocketError)));
    connect(server,SIGNAL(newConnection()),this,SLOT(newConnect()));
#endif

}
/*
    函数名:
    参数:socketError为网络使用的错误描术符
    返回值:无
    作用:
    网络出错处理
*/
void Robot::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        emit netError(tr("The host was not found. Please check the "
                         "host name and port settings."));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        emit netError(tr("The connection was refused by the peer. "
                         "Make sure the server is running, "
                         "and check that the host name and port "
                         "settings are correct."));
        break;
    default:
        emit netError(tr("The following error occurred: %1.")
                      .arg(tcpClient->errorString()));
    }
}
/*
    函数名:tcpDate
    参数:无
    返回值:无
    作用:
    处理TCP数据
*/
void Robot::tcpDate()
{

    QByteArray data=tcpClient->readAll();
    qDebug()<<data.data()<<data.size();
    if(QString(data.data()).contains("Ready"))
    {
        tcpClient->write("OK",3);

    }
    if(QString(data.data()).contains("START")|QString(data.data()).contains("Done"))
        emit takeAPhoto();



}

void Robot::makeAMove()
{
     tcpClient->write("NEXT",3);

}
void Robot::detectNG()
{
    tcpClient->write("NG",3);
}
void Robot::stopMove()
{
     tcpClient->write("Stop",5);

}
/*
    函数名:netConnect()
    参数:无
    返回值:无
    作用:
    当有新的TCP连接到来时,获取客户端socket
*/
void Robot::newConnect()
{
    if(server->hasPendingConnections())
    {
        tcpClient=server->nextPendingConnection();

        connect(tcpClient, SIGNAL(error(QAbstractSocket::SocketError)),
               this, SLOT(displayError(QAbstractSocket::SocketError)));

        connect(tcpClient,SIGNAL(readyRead()),this,SLOT(tcpDate()));
    }
}
