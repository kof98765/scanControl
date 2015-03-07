#include "msghandlerwapper.h"
#include <QtCore/QMetaType>
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include <QtCore/QCoreApplication>

static void msgHandlerFunction(QtMsgType type,const QMessageLogContext &con,const QString &str)
{


    QMetaObject::invokeMethod(MsgHandlerWapper::instance(), "message"
                        , Q_ARG(QtMsgType, type)
                        , Q_ARG(QString,str));

}

MsgHandlerWapper * MsgHandlerWapper::m_instance = 0;

MsgHandlerWapper * MsgHandlerWapper::instance()
{
    static QMutex mutex;
    if (!m_instance) {
        QMutexLocker locker(&mutex);
        if (!m_instance)
            m_instance = new MsgHandlerWapper;
    }

    return m_instance;
}

MsgHandlerWapper::MsgHandlerWapper()
    :QObject(qApp)
{
    qRegisterMetaType<QtMsgType>("QtMsgType");

    qInstallMessageHandler(msgHandlerFunction);
}
