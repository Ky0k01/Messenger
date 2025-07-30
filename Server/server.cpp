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

    QSqlQuery q;
    if(!q.exec("CREATE TABLE IF NOT EXISTS users (login VARCHAR(64) PRIMARY KEY, password VARCHAR(64) NOT NULL);")){
        qCritical() << "Failed to create table:" << q.lastError().text();
        exit(1);
    }
}

void MessengerServer::onNewConnection() {
    QWebSocket *socket = server->nextPendingConnection();

    connect(&timer, &QTimer::timeout, socket, &QWebSocket::ping);
    timer.start(5000);
    connect(socket, &QWebSocket::textMessageReceived, this, [=](const QString &msg){
        QJsonDocument doc = QJsonDocument::fromJson(msg.toUtf8());
        QJsonObject obj = doc.object();
        QString cmd=obj["package"].toString();
        QString login = obj["login"].toString();
        QString password = obj["password"].toString();

        qDebug()<<"received package:\n"<<
                  "cmd - "<<cmd<<"\n"
                  "login - "<<login<<"\n"
                  "password - "<<password<<"\n";

        QJsonObject reply;
        if(cmd == "register"){
            qDebug()<<"trying to register user";

            QSqlQuery q;
            q.prepare("INSERT INTO users (login, password) VALUES (:login, :password);");
            q.bindValue(":login", login);
            q.bindValue(":password", password);
            if(q.exec()){
                reply["status"] = "ok";
                reply["message"] = "User registered successfully";
                qDebug()<<"status ok";
            }
            else{
                reply["status"] = "error";
                reply["error"] = "User exists or database error";
                qDebug()<<"status error"<<q.lastError().text();
            }
        }
        else if (cmd == "login"){
            qDebug()<<"trying to login user";

            QSqlQuery q;
            q.prepare("SELECT password FROM users WHERE login = :login;");
            q.bindValue(":login", login);
            if(q.exec() && q.next() && q.value(0).toString() == password){
                reply["status"] = "ok";
                qDebug() << "Login successful for user:" << login;
            }
            else{
                reply["status"] = "error";
                reply["error"] = "Invalid login or password";
                qDebug() << "Login failed for user:" << login << "Error:" << (q.lastError().isValid() ? q.lastError().text() : "Invalid credentials");
            }
        }
        socket->sendTextMessage(QJsonDocument(reply).toJson(QJsonDocument::Compact));
    });
    connect(socket, &QWebSocket::disconnected, socket, &QWebSocket::deleteLater);
}
