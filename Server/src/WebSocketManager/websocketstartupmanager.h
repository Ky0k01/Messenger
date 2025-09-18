#ifndef WEBSOCKETSTARTUPMANAGER_H
#define WEBSOCKETSTARTUPMANAGER_H

#include <QObject>
#include <QWebSocket>
#include <QWebSocketServer>
#include <QSslCertificate>

class WebSocketStartupManager : public QObject{
    Q_OBJECT
public:
    explicit WebSocketStartupManager(QWebSocketServer* server, QObject *parent = nullptr);
    ~WebSocketStartupManager();

public slots:
    QWebSocketServer *startServer();

signals:

private:
    QWebSocketServer* server;
};

#endif // WEBSOCKETSTARTUPMANAGER_H
