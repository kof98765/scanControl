#ifndef REFLECTCONTROL_H
#define REFLECTCONTROL_H

#include <QUdpSocket>
#include <QThread>
#include <QDir>
#include <QSettings>
class reflectControl:public QThread
{
    Q_OBJECT
public:
    reflectControl();
    void initSocked(QString remote,int udpport);
    void sendMsg(QString msg,QString receive,int receivePort);
    bool copyDirectoryFiles(QString sourceDir ,QString toDir, bool coverFileIfExist);

private:
      QUdpSocket *udp;
      int port;
      QString localPath,remotePath;
      QString currentConfigFile;
      QString receiveHost;
      QSettings set;


public slots:
    void udpDate();
    void takeAPhoto();
    void setConfigFile(QString fileName);
    void setImgFilePath(QString filePath);
    void setServerPort(int Port);
    void displayError(QAbstractSocket::SocketError socketError);
signals:
    void makeAMove();
    void startDetect();
    void recvData(char *);
    void Error(QString);
    void netTest(QString);



};

#endif // REFLECTCONTROL_H
