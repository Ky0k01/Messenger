#ifndef RECEIVECOMMAND_H
#define RECEIVECOMMAND_H

#include <QObject>
#include <QWebSocketServer>
#include <QJsonDocument>
#include <QJsonObject>

#include "../../Interface/icommand.h"

class ReceiveCommandManager : public QObject{
    Q_OBJECT
public:
    explicit ReceiveCommandManager(QWebSocketServer* server, QObject *parent = nullptr):
        server(server), QObject(parent){

    }

public slots:
    void processReceivedMessage(const QJsonObject& obj, int senderId){
        if(obj["package"].toString() == "Registration"){

        }
        else if(obj["package"].toString() == "Login"){

        }
        else if(obj["package"].toString() == "message"){

        }
        else if(obj["package"].toString() == "Users list"){

        }
        else if(obj["package"].toString() == "User status"){

        }
        else if(obj["package"].toString() == "Error"){

        }
    }

    void processReceivedFile(){

    }

signals:

private:
    QWebSocketServer* server;
};

#endif // RECEIVECOMMAND_H
