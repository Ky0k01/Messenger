#include "server.h"

Server::Server(quint16 port, QObject *parent): QObject(parent){
    server = new QWebSocketServer(QStringLiteral("Messenger Server"), QWebSocketServer::NonSecureMode, this);

    if(!server->listen(QHostAddress::Any, port)){
        qCritical("Failed to open web socket server");
        exit(1);
    }

    connect(server, &QWebSocketServer::newConnection, this, &Server::onNewConnection);

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
    if(!q.exec("CREATE TABLE IF NOT EXISTS users (id BIGSERIAL PRIMARY KEY, login VARCHAR(64) NOT NULL, password VARCHAR(64) NOT NULL)")){
        qCritical() << "Failed to create table:" << q.lastError().text();
        exit(1);
    }
    qDebug()<<"Server URL: "<<server->serverName()<<server->serverUrl()<<server->serverAddress()<<server->serverPort();
}

void Server::onNewConnection() {
    while(server->hasPendingConnections()){
        QWebSocket *socket = server->nextPendingConnection();

//        connect(&timer, &QTimer::timeout, socket, &QWebSocket::ping);
//        timer.start(5000);

        connect(socket, &QWebSocket::textMessageReceived,   this,   &Server::textMessageReceived);
        connect(socket, &QWebSocket::binaryMessageReceived, this,   &Server::binaryMessageReceived);
        connect(socket, &QWebSocket::disconnected,          socket, &QWebSocket::deleteLater);
    }
}

void Server::textMessageReceived(const QString& message){
    QWebSocket* socket = qobject_cast<QWebSocket*>(sender());

    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
    QJsonObject obj = doc.object();
    QString cmd=obj["package"].toString();
    QString login = obj["login"].toString();
    QString password = obj["password"].toString();

    qDebug()<<"received package:\n"<<
              "package - "<<cmd<<"\n"
              "login - "<<login<<"\n"
              "password - "<<password<<"\n";

    QJsonObject reply;
    if(cmd == "Registration"){
        qDebug()<<"trying to register user";

        QSqlQuery q;
        q.prepare("INSERT INTO users (login, password) "
                  "VALUES (:login, :password) ");
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
        q.prepare("SELECT login, password "
                  "FROM users "
                  "WHERE login = :login "
                  "AND password = :password ");
        q.bindValue(":login", login);
        q.bindValue(":password", password);

        if(q.exec()){
            if (q.next()){
                reply["status"] = "ok";
                reply["message"] = "User logined successfully";
                qDebug() << "Login successful for user:" << login;
            }
            else{
                reply["status"] = "error";
                reply["error"] = "Invalid login or password";
                qDebug()<<"Invalid login or password";
            }
        }
        else{
            qDebug()<<"Invalid query"<<q.lastError().text();
        }
    }
    socket->sendTextMessage(QJsonDocument(reply).toJson(QJsonDocument::Compact));
}

void Server::binaryMessageReceived(const QByteArray& message){

}
