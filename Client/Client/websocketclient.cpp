#include "websocketclient.h"

#include <QJsonDocument>
#include <QJsonObject>

WebSocketClient::WebSocketClient(const QUrl &url, QObject *parent): QObject(parent), m_url(url){
    connect(&m_webSocket, &QWebSocket::connected, this, &WebSocketClient::onConnected);
    connect(&m_webSocket, &QWebSocket::textMessageReceived, this, &WebSocketClient::onTextMessageReceived);
    m_webSocket.open(m_url);
}

void WebSocketClient::sendLoginRequest(const QString &login, const QString &password){
    QJsonObject obj;
    obj["package"] = "login";
    obj["login"] = login;
    obj["password"] = password;
    m_webSocket.sendTextMessage(QJsonDocument(obj).toJson(QJsonDocument::Compact));

    qDebug() << "Login request sent:" << QJsonDocument(obj).toJson(QJsonDocument::Compact);
}

void WebSocketClient::sendRegisterRequest(const QString &login, const QString &password){
    QJsonObject obj;
    obj["package"] = "Registration";
    obj["login"] = login;
    obj["password"] = password;
    m_webSocket.sendTextMessage(QJsonDocument(obj).toJson(QJsonDocument::Compact));

    qDebug() << "Register request sent:" << QJsonDocument(obj).toJson(QJsonDocument::Compact);
}

void WebSocketClient::onConnected(){
    qDebug() << "WebSocket connected to" << m_url.toString();
    // Можно отправить приветствие или запрос состояния
}

void WebSocketClient::onTextMessageReceived(const QString &message)
{
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
    QJsonObject obj = doc.object();

    if (obj["status"] == "ok") {
//        bool ok = obj["success"].toBool();
//        emit loginResult(ok, obj["error"].toString());
        qDebug()<<"Received package status"<<obj["status"].toString()<<", message - "<<obj["message"].toString();
//        qDebug() << "Login result received:" << (ok ? "Success" : "Failure") << obj["error"].toString();
    }
//    else if (obj["status"] == "register") {
////        bool ok = obj["success"].toBool();
////        emit registrationResult(ok, obj["error"].toString());
//        qDebug()<<"";
////        qDebug() << "Registration result received:" << (ok ? "Success" : "Failure") << obj["error"].toString();
//    }
    else if(obj["status"] == "error"){
        qDebug()<<"Received package status"<<obj["status"].toString()<<", error - "<<obj["error"].toString();
    }
}


