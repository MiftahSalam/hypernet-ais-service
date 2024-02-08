#ifndef AISOUTPUT_WEBSOCKETSERVER_H
#define AISOUTPUT_WEBSOCKETSERVER_H

#include "ais_output.h"

#include <QWebSocketServer>

class AISOutput_WebSocketServer: public AISOutput
{
public:
    AISOutput_WebSocketServer(QObject *parent = nullptr, AISOutputService* service = nullptr, QString cfg = "");

    // AISOutput interface
    void Open() override;

protected:
    virtual void SendRaw(const QByteArray data) override;
    void Close() override;
    void InitConfig() override;

private slots:
    void onNewConnection();
    void onSocketDisconnected();

private:
    QWebSocketServer *server;
    QList<QWebSocket*> m_clients;
    QString url;
    QString host;
    int port;
};

#endif // AISOUTPUT_WEBSOCKETSERVER_H
