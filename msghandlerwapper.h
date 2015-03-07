/*
  (C) 2011 dbzhang800#gmail.com
*/
#ifndef MSGHANDLERWAPPER_H
#define MSGHANDLERWAPPER_H
#include <QtCore/QObject>
#include <QDebug>
#include <QFile>
class MsgHandlerWapper:public QObject
{
    Q_OBJECT
public:
    static MsgHandlerWapper * instance();

signals:
    void message(QtMsgType,const QString &message);

private:
    MsgHandlerWapper();
    QFile f;
    static MsgHandlerWapper * m_instance;
};

#endif // MSGHANDLERWAPPER_Hs
