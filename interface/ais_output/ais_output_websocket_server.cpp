#include "ais_output_websocket_server.h"

#include <QWebSocket>

#ifdef USE_LOG4QT
#include <log4qt/logger.h>
LOG4QT_DECLARE_STATIC_LOGGER(logger, AISOutput_WebSocketServer)
#else
#include <QDebug>
#endif

AISOutput_WebSocketServer::AISOutput_WebSocketServer(QObject *parent, AISOutputService* service, QString cfg)
    : AISOutput(parent, service, cfg)
{
#ifdef USE_LOG4QT
    if(!service) logger()->fatal("ais output service is null");
#else
    if(!service) qFatal("ais output service is null");
#endif

    server = nullptr;
}

AISOutput_WebSocketServer::~AISOutput_WebSocketServer()
{
    for (auto client : m_clients) {
        client->close();
    }
}

void AISOutput_WebSocketServer::onNewConnection()
{
    QWebSocket *pSocket = server->nextPendingConnection();

    connect(pSocket, &QWebSocket::disconnected, this, &AISOutput_WebSocketServer::onSocketDisconnected);

    m_clients << pSocket;

#ifdef USE_LOG4QT
    logger()->info()<<Q_FUNC_INFO<<" - new connection: peer name -> "<<pSocket->peerName()<<", peer address -> "<<pSocket->peerAddress().toString();
#else
    qInfo()<<Q_FUNC_INFO<<" - new connection: peer name -> "<<pSocket->peerName()<<", peer address -> "<<pSocket->peerAddress().toString();
#endif
}

void AISOutput_WebSocketServer::onSocketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());

#ifdef USE_LOG4QT
    logger()->info()<<Q_FUNC_INFO<<" - client disconnected: peer name -> "<<pClient->peerName()<<", peer address -> "<<pClient->peerAddress().toString();
#else
    qInfo()<<Q_FUNC_INFO<<" - client disconnected: peer name -> "<<pClient->peerName()<<", peer address -> "<<pClient->peerAddress().toString();
#endif

    if (pClient) {
        m_clients.removeAll(pClient);
        pClient->deleteLater();
    }
}

void AISOutput_WebSocketServer::Open()
{
    InitConfig();

    if (server)
    {
        disconnect(server, &QWebSocketServer::newConnection, this, &AISOutput_WebSocketServer::onNewConnection);
        server->close();
        delete server;
    }

    server = new QWebSocketServer("AIS Service...", QWebSocketServer::NonSecureMode, this);
    if (server->listen(QHostAddress(host), port)) {
#ifdef USE_LOG4QT
        logger()->info()<<Q_FUNC_INFO<<" - ais output webserver listening on url "<<url;
#else
        qInfo()<<Q_FUNC_INFO<<" - ais output webserver listening on url "<<url;
#endif
    } else {
#ifdef USE_LOG4QT
        logger()->warn()<<Q_FUNC_INFO<<" - ais output webserver cannot listen on url "<<url<<" with error: "<<server->errorString();
#else
        qWarning()<<Q_FUNC_INFO<<" - ais output webserver cannot listen on url "<<url<<" with error: "<<server->errorString();
#endif
    }

    connect(server, &QWebSocketServer::newConnection, this, &AISOutput_WebSocketServer::onNewConnection);
}

void AISOutput_WebSocketServer::SendRaw(const QByteArray data)
{
    for (auto client : m_clients) {
        client->sendBinaryMessage(data);
    }

    if (server)
    {
        disconnect(server, &QWebSocketServer::newConnection, this, &AISOutput_WebSocketServer::onNewConnection);
        server->close();
        delete server;
    }
}

void AISOutput_WebSocketServer::Close()
{
}

void AISOutput_WebSocketServer::InitConfig()
{
#ifdef USE_LOG4QT
    logger()->debug()<<Q_FUNC_INFO<<" - config: "<<m_config;
#else
    qDebug()<<Q_FUNC_INFO<<" - config: "<<m_config;
#endif

#if QT_VERSION > QT_VERSION_CHECK(5, 13, 0)
    QStringList config_list = m_config.split(";", Qt::SkipEmptyParts);
#else
    QStringList config_list = m_config.split(";", QString::SkipEmptyParts);
#endif
    if(config_list.size() == 4)
    {
        url = config_list.at(0);
#if QT_VERSION > QT_VERSION_CHECK(5, 13, 0)
        QStringList url_split = url.split(":", Qt::SkipEmptyParts);
#else
        QStringList url_split = url.split(":", QString::SkipEmptyParts);
#endif
        if(url_split.size() == 2)
        {
            bool ok;

            host = url_split.at(0);
            auto portStr = url_split.at(1);
            port = portStr.toInt(&ok);

            if (!ok) {
                port = 8083;
#ifdef USE_LOG4QT
                logger()->warn()<<Q_FUNC_INFO<<" - invalid port "<<portStr<<". will use default 8083";
#else
                qWarning()<<Q_FUNC_INFO<<" - invalid port "<<portStr<<". will use default 8083";
#endif
            }
        }
#ifdef USE_LOG4QT
        else logger()->fatal("invalid url config %s", url.toUtf8().constData());
#else
        else qFatal("invalid url config %s", url.toUtf8().constData());
#endif
    }
#ifdef USE_LOG4QT
    else logger()->fatal("invalid config %s", m_config.toUtf8().constData());
#else
    else qFatal("invalid config %s", m_config.toUtf8().constData());
#endif
}
