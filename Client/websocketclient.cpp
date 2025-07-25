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
    obj["action"] = "login";
    obj["login"] = login;
    obj["password"] = password;
    m_webSocket.sendTextMessage(QJsonDocument(obj).toJson(QJsonDocument::Compact));
}

void WebSocketClient::sendRegisterRequest(const QString &login, const QString &password){
    QJsonObject obj;
    obj["action"] = "register";
    obj["login"] = login;
    obj["password"] = password;
    m_webSocket.sendTextMessage(QJsonDocument(obj).toJson(QJsonDocument::Compact));
}

void WebSocketClient::onConnected(){
    // Можно отправить приветствие или запрос состояния
}

void WebSocketClient::onTextMessageReceived(const QString &message)
{
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
    QJsonObject obj = doc.object();

    if (obj["action"] == "login") {
        bool ok = obj["success"].toBool();
        emit loginResult(ok, obj["error"].toString());
    }
    else if (obj["action"] == "register") {
        bool ok = obj["success"].toBool();
        emit registrationResult(ok, obj["error"].toString());
    }
}
