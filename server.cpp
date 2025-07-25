#include "server.h"

MessengerServer::MessengerServer(quint16 port, QObject *parent): QObject(parent){
    server = new QWebSocketServer(QStringLiteral("Messenger Server"), QWebSocketServer::NonSecureMode, this);

    if(!server->listen(QHostAddress::Any, port)){
        qCritical("Failed to open web socket server");
        exit(1);
    }

    connect(server, &QWebSocketServer::newConnection, this, &MessengerServer::onNewConnection);

    db=QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setDatabaseName("messenger_db");
    db.setUserName("postgres");
    db.setPassword("2905");

    if(!db.open()){
        qCritical() << "Database connection failed:" << db.lastError().text();
        exit(1);
    }

    QSqlQuery q("CREATE TABLE IF NOT EXISTS users (login VARCHAR PRIMARY KEY, password VARCHAR NOT NULL);");

    if(!q.exec()){
        qCritical() << "Failed to create table:" << q.lastError().text();
        exit(1);
    }
}

void MessengerServer::onNewConnection() {
    QWebSocket *socket = server->nextPendingConnection();

    connect(socket, &QWebSocket::textMessageReceived, this, [=](const QString &msg){
        QJsonDocument doc = QJsonDocument::fromJson(msg.toUtf8());
        QJsonObject obj = doc.object();
        QString cmd=obj["cmd"].toString();
        QString login = obj["login"].toString();
        QString password = obj["password"].toString();

        QJsonObject reply;
        if(cmd == "register"){
            QSqlQuery q;
            q.prepare("INSERT INTO users (login, password) VALUES (:login, :password);");
            q.bindValue(":login", login);
            q.bindValue(":password", password);
            if(q.exec()){
                reply["status"] = "ok";
            }
            else{
                reply["status"] = "error";
                reply["error"] = "User exists or database error";
            }
        }
        else if (cmd == "login"){
            QSqlQuery q;
            q.prepare("SELECT password FROM users WHERE login = :login;");
            q.bindValue(":login", login);
            if(q.exec() && q.next() && q.value(0).toString() == password){
                reply["status"] = "ok";
            }
            else{
                reply["status"] = "error";
                reply["error"] = "Invalid login or password";
            }
        }
        socket->sendTextMessage(QJsonDocument(reply).toJson(QJsonDocument::Compact));
    });
    connect(socket, &QWebSocket::disconnected, socket, &QWebSocket::deleteLater);
}
