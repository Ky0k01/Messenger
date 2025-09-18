#include "websocketstartupmanager.h"

WebSocketStartupManager::WebSocketStartupManager(QWebSocketServer* server, QObject *parent)
    : server(server), QObject(parent){

}

WebSocketStartupManager::~WebSocketStartupManager(){
    if(server->isListening()) server->close();
}

QWebSocketServer* WebSocketStartupManager::startServer(){
    return server = new QWebSocketServer(QStringLiteral("Messenger Server"), QWebSocketServer::NonSecureMode, this);
}


