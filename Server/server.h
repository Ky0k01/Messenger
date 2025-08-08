#ifndef SERVER_H
#define SERVER_H

#include <QWebSocketServer>
#include <QWebSocket>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include <QJsonDocument>
#include <QJsonObject>

#include <QTimer>

class Server : public QObject{
    Q_OBJECT

public:
    Server(quint16 port, QObject *parent = nullptr);

public slots:
    void onNewConnection();
    void textMessageReceived(const QString& message);
    void binaryMessageReceived(const QByteArray& message);

private:
    QWebSocketServer *server;
    QSqlDatabase db;

    QTimer timer;
};

#endif // SERVER_H
