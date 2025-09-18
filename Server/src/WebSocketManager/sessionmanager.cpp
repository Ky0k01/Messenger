#include "sessionmanager.h"

SessionManager::SessionManager(QObject *parent): QObject(parent){

}

SessionManager::~SessionManager(){
    anonymousSocket.clear();
    userSessions.clear();
}

void SessionManager::registerAnonymousSocket(QWebSocket* socket){
    anonymousSocket.append(socket);
}

void SessionManager::registerUser(const QString &userId, QWebSocket *socket){
    userSessions[userId] = socket;
    anonymousSocket.removeAll(socket);
}

void SessionManager::deleteUser(const QString &userId){
    userSessions.remove(userId);
}

void SessionManager::deleteSocket(QWebSocket *socket){
    userSessions.erase(std::find_if(userSessions.begin(), userSessions.end(), [socket](const QWebSocket* s){
        return s == socket;
    }));

    anonymousSocket.removeAll(socket);
}

QWebSocket *SessionManager::getSocketByUserId(const QString &userId) const{
    return userSessions.value(userId, nullptr);
}
