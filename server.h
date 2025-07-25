#ifndef SERVER_H
#define SERVER_H

#include <QtWebSockets/QWebSocketServer>
#include <QtWebSockets/QWebSocket>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

#include <QJsonDocument>
#include <QJsonObject>

class MessengerServer : public QObject{
    Q_OBJECT

public:
    MessengerServer(quint16 port, QObject *parent = nullptr);

public slots:
    void onNewConnection();

private:
    QWebSocketServer *server;
    QSqlDatabase db;

};

#endif // SERVER_H
