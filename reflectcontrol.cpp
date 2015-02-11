#include "reflectcontrol.h"

reflectControl::reflectControl()
{
    /*
    如果没有img文件夹,就创建一个,用于存放待检测图片
    */
    QDir dir("img");
    if(!dir.exists())
        dir.mkdir(dir.absolutePath());
    udp=new QUdpSocket();
}
/*
    函数名:initSocket
    参数:remote为远程目录IP,udpport为UDP端口
    作用:
    初始化UDP网络,并绑定端口
*/
void reflectControl::initSocked(QString remote,int udpport)
{
    remotePath=remote;
    port=udpport;

    udp->bind(port,QUdpSocket::ReuseAddressHint);

    connect(udp,SIGNAL(readyRead()),this,SLOT(udpDate()));
    connect(udp, SIGNAL(error(QAbstractSocket::SocketError)),
               this, SLOT(displayError(QAbstractSocket::SocketError)));
}
/*
    函数名:udpDate
    参数:无
    返回值:无
    作用:
    处理UDP数据
*/
void reflectControl::udpDate()
{
    QByteArray *data=new QByteArray;
    QHostAddress sender;
    quint16 senderPort;

    while(udp->hasPendingDatagrams())
        {
            data->resize(udp->pendingDatagramSize());
            udp->readDatagram(data->data(),data->size(),&sender,&senderPort);
            qDebug()<<sender.toString()<<senderPort<<data->data()<<data->size();
            emit recvData(data->data());

         }


}

void reflectControl::setConfigFile(QString fileName)
{

}

void reflectControl::takeAPhoto()
{
    sendMsg("photo",remotePath,port);
    //emit startDetect();
    //emit makeAMove();
}
void reflectControl::sendMsg(QString msg,QString address,int sendport)
{
     QByteArray data=msg.toUtf8();

    udp->writeDatagram(data.data(), data.size(),
                                 QHostAddress(address), sendport);


}


void reflectControl::setImgFilePath(QString filePath)
{
    remotePath=filePath;
}

void reflectControl::setServerPort(int Port)
{
    port=Port;
}
void reflectControl::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        emit Error(tr("The host was not found. Please check the "
                         "host name and port settings."));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        emit Error(tr("The connection was refused by the peer. "
                         "Make sure the server is running, "
                         "and check that the host name and port "
                         "settings are correct."));
        break;
    default:
        emit Error(tr("The following error occurred: %1.")
                      .arg(udp->errorString()));
    }
}

bool reflectControl::copyDirectoryFiles(QString fromDir ,QString toDir, bool coverFileIfExist)
{
    QDir sourceDir(fromDir);
        QDir targetDir(toDir);
        if(!targetDir.exists()){    /**< 如果目标目录不存在，则进行创建 */
            if(!targetDir.mkdir(targetDir.absolutePath()))
                return false;
        }

        QFileInfoList fileInfoList = sourceDir.entryInfoList();
        foreach(QFileInfo fileInfo, fileInfoList){
            if(fileInfo.fileName() == "." || fileInfo.fileName() == "..")
                continue;

            if(fileInfo.isDir()){    /**< 当为目录时，递归的进行copy */
                if(!copyDirectoryFiles(fileInfo.filePath(),
                    targetDir.filePath(fileInfo.fileName()),
                    coverFileIfExist))
                    return false;
            }
            else{            /**< 当允许覆盖操作时，将旧文件进行删除操作 */
                if(coverFileIfExist && targetDir.exists(fileInfo.fileName())){
                    targetDir.remove(fileInfo.fileName());
                }

                /// 进行文件copy
                if(!QFile::copy(fileInfo.filePath(),
                    targetDir.filePath(fileInfo.fileName()))){
                        return false;
                }
            }
        }
        return true;
}
