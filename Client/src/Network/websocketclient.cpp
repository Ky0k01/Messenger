#include "websocketclient.h"

WebSocketClient::WebSocketClient(ReceiveCommand* receiveCommandManager, const QUrl &url, QObject *parent)
    : QObject(parent), url(url), receiveCommandManager(receiveCommandManager){


    connect(&socket,    &QWebSocket::connected,             this, &WebSocketClient::onConnected);
    connect(&socket,    &QWebSocket::pong,                  this, &WebSocketClient::onPongReceived);
    connect(&pingTimer, &QTimer::timeout,                   this, &WebSocketClient::sendPing);

    connect(&socket, &QWebSocket::textMessageReceived,      this, &WebSocketClient::onTextMessageReceived);
    connect(&socket, &QWebSocket::binaryMessageReceived,    this, &WebSocketClient::onBinaryMessageReceived);

    socket.open(url);
    qDebug()<<"соединение есть";
}

void WebSocketClient::connections(){
    connect(&socket,    &QWebSocket::connected,             this, &WebSocketClient::onConnected);
    connect(&socket,    &QWebSocket::pong,                  this, &WebSocketClient::onPongReceived);
    connect(&pingTimer, &QTimer::timeout,                   this, &WebSocketClient::sendPing);

    connect(&socket, &QWebSocket::textMessageReceived,      this, &WebSocketClient::onTextMessageReceived);
    connect(&socket, &QWebSocket::binaryMessageReceived,    this, &WebSocketClient::onBinaryMessageReceived);

    connect(this, &WebSocketClient::sendReceivedMessage,    receiveCommandManager, &ReceiveCommand::onTextMessageReceived);
    connect(this, &WebSocketClient::sendReceivedFile,       receiveCommandManager, &ReceiveCommand::onBinaryMessageReceived);
}

WebSocketClient::~WebSocketClient(){
    socket.close();
}

void WebSocketClient::onConnected(){
    sendPing();
    pingTimer.start(5000);
}

void WebSocketClient::sendPing(){
    socket.ping("ping");
}

void WebSocketClient::onPongReceived(quint64 elapsedTime, const QByteArray& payLoad){
    qDebug()<<"Pong received in"<<elapsedTime<<"ms, payload:"<<payLoad;
}


//void WebSocketClient::onTextMessageReceived(const QString &message){
//    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
//    QJsonObject obj = doc.object();

//    QString package = obj["package"].toString();
//    bool success;
//    if(obj["success"] == "ok"){
//        success = true;
//    }
//    else{
//        success = false;
//    }
//    QString msg = obj["message"].toString();

//    qDebug()<<"Received package:\n"<<
//              package<<"\n"<<
//              success<<"\n"<<
//              msg;

//    if(package == "Registration"){
//        emit sendRegistrationResult(success, msg);
//    }
//    else if(package == "Login"){
//        emit sendLoginResult(success, msg);
//    }
//    else{
//        qDebug("Received undeclared package");
//    }
//}

//void WebSocketClient::onBinaryMessageReceived(const QByteArray& message){

//}
