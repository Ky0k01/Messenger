#ifndef WEBSOCKETMANAGER_H
#define WEBSOCKETMANAGER_H

#include <QWebSocket>
#include <QWebSocketServer>
#include <QSslCertificate>
#include <QJsonObject>
#include <QJsonDocument>

#include <iostream>
#include <exception>

#include "sessionmanager.h"
#include "../Logger/logger.h"
//#include "../mediator.h"

using namespace std;

class WebSocketException : public exception{
public:
    WebSocketException(const string& msg) : message(msg){}

    const char* what() const noexcept override {
        return message.c_str();
    }

private:
    string message;
};


class WebSocketManager : public QObject{
    Q_OBJECT
public:
    explicit WebSocketManager(Logger* logger, QObject *parent = nullptr);

public slots:
    void onNewConnection();

signals:
    void writeAnonymousSocket(QWebSocket* socket);

private slots:
    void onPongReceived(quint64 elapsedTime, const QByteArray& payLoad);

    void textMessageReceived(const QString& message);

    void binaryMessageReceived(const QByteArray& message);

    void command(const QString& line){
        qDebug()<<line;
        // обработка команд
    }

private:
    Logger *logger;
    QWebSocketServer* server;
};

#endif // WEBSOCKETMANAGER_H
