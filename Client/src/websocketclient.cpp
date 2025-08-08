#include "websocketclient.h"

WebSocketClient::WebSocketClient(const QUrl &url, QObject *parent): QObject(parent), m_url(url){
    connect(&m_webSocket, &QWebSocket::connected,               this, &WebSocketClient::onConnected);
    connect(&m_webSocket, &QWebSocket::textMessageReceived,     this, &WebSocketClient::onTextMessageReceived);
    connect(&m_webSocket, &QWebSocket::binaryMessageReceived,   this, &WebSocketClient::onBinaryMessageReceived);
    m_webSocket.open(m_url);
    qDebug()<<"соединение есть";
}

WebSocketClient::~WebSocketClient(){
    m_webSocket.close();
}

void WebSocketClient::sendLoginRequest(const QString &login, const QString &password){
    QJsonObject obj;
    obj["package"] = "Login";
    obj["login"] = login;
    obj["password"] = password;
    m_webSocket.sendTextMessage(QJsonDocument(obj).toJson(QJsonDocument::Compact));

    qDebug() << "Login request sent:" << QJsonDocument(obj).toJson(QJsonDocument::Compact);
}

void WebSocketClient::sendRegistrationRequest(const QString &login, const QString &password){
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

void WebSocketClient::onTextMessageReceived(const QString &message){
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
    QJsonObject obj = doc.object();

    QString package = obj["package"].toString();
    bool success;
    if(obj["success"] == "ok"){
        success = true;
    }
    else{
        success = false;
    }
    QString msg = obj["message"].toString();

    qDebug()<<"Received package:\n"<<
              package<<"\n"<<
              success<<"\n"<<
              msg;

    if(package == "Registration"){
        emit sendRegistrationResult(success, msg);
    }
    else if(package == "Login"){
        emit sendLoginResult(success, msg);
    }
    else{
        qDebug("Received undeclared package");
    }
}

void WebSocketClient::onBinaryMessageReceived(const QByteArray& message){

}
