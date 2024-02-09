#include "ais_output_websocket_server.h"

#include <QWebSocket>

AISOutput_WebSocketServer::AISOutput_WebSocketServer(QObject *parent, AISOutputService* service, QString cfg)
    : AISOutput(parent, service, cfg)
{
    if(!service) qFatal("ais output service is null");

    server = nullptr;
}

void AISOutput_WebSocketServer::onNewConnection()
{
    QWebSocket *pSocket = server->nextPendingConnection();

    connect(pSocket, &QWebSocket::disconnected, this, &AISOutput_WebSocketServer::onSocketDisconnected);

    m_clients << pSocket;

    qInfo()<<Q_FUNC_INFO<<"new connection: peer name ->"<<pSocket->peerName()<<", peer address ->"<<pSocket->peerAddress();
}

void AISOutput_WebSocketServer::onSocketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());

    qInfo()<<Q_FUNC_INFO<<"client disconnected: peer name ->"<<pClient->peerName()<<", peer address ->"<<pClient->peerAddress();

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
        qInfo()<<Q_FUNC_INFO<<"ais output webserver listening on url"<<url;
    } else {
        qWarning()<<Q_FUNC_INFO<<"ais output webserver cannot listen on url"<<url<<" with error"<<server->errorString();
    }

    connect(server, &QWebSocketServer::newConnection, this, &AISOutput_WebSocketServer::onNewConnection);
}

void AISOutput_WebSocketServer::SendRaw(const QByteArray data)
{
    for (auto client : m_clients) {
        client->sendBinaryMessage(data);
    }
}

void AISOutput_WebSocketServer::Close()
{
}

void AISOutput_WebSocketServer::InitConfig()
{
    qDebug()<<Q_FUNC_INFO<<"config"<<m_config;

#if QT_VERSION > QT_VERSION_CHECK(5, 13, 0)
    QStringList config_list = m_config.split(";", Qt::SkipEmptyParts);
#else
    QStringList config_list = m_config.split(":", QString::SkipEmptyParts);
#endif
    if(config_list.size() == 3)
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
                qWarning()<<Q_FUNC_INFO<<"invalid port"<<portStr<<". will use default 8083";
            }
        }
        else qFatal("invalid url config %s", url.toUtf8().constData());
    }
    else qFatal("invalid config %s", m_config.toUtf8().constData());
}
