#include "websocketmanager.h"

WebSocketManager::WebSocketManager(Logger *logger, QObject *parent): logger(logger), QObject(parent){

}

void WebSocketManager::onNewConnection(){
    while(server->hasPendingConnections()){
        QWebSocket *socket = server->nextPendingConnection();

        connect(socket, &QWebSocket::pong, this, &WebSocketManager::onPongReceived);

        connect(socket, &QWebSocket::textMessageReceived,   this,   &WebSocketManager::textMessageReceived);
        connect(socket, &QWebSocket::binaryMessageReceived, this,   &WebSocketManager::binaryMessageReceived);

        connect(socket, &QWebSocket::disconnected,          socket, &QWebSocket::deleteLater);

        emit writeAnonymousSocket(socket);
    }
}

void WebSocketManager::onPongReceived(quint64 elapsedTime, const QByteArray &payLoad){
    qDebug()<<"Pong received in"<<elapsedTime<<"ms, payload:"<<payLoad;
}

void WebSocketManager::textMessageReceived(const QString &message){
    QWebSocket* socket = qobject_cast<QWebSocket*>(sender());

    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
    QJsonObject obj = doc.object();

//    emit processCommand(obj);
}

void WebSocketManager::binaryMessageReceived(const QByteArray &message){

}
