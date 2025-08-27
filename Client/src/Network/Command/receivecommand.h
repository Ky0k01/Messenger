#ifndef RECEIVECOMMAND_H
#define RECEIVECOMMAND_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QDebug>

#include "icommand.h"

class ReceiveCommand : public QObject{
    Q_OBJECT
public:
    explicit ReceiveCommand(QObject* parent = nullptr) : QObject(parent){}

public slots:
    void onTextMessageReceived(const QJsonObject& obj){
        QString messageType = obj["package"].toString();

        // обработка каждого пакета будет вынесена в отдельную функцию
        if (messageType == "Registration"){
            QMessageBox::information(nullptr, tr("Registration"), tr("Registration successful!"));
        }
        else if (messageType == "Login"){
            emit openChatWindow();
        }
        else if (messageType == "message"){
            readMessage(obj["sender_username"].toString(), obj["message"].toString(), obj["timestamp"].toString());
        }
        else if (messageType == "Users list"){

        }
        else if (messageType == "User status"){

        }
        else if (messageType == "Error"){
            QMessageBox::warning(nullptr, obj["ErrorType"].toString(), obj["message"].toString());
//            if (obj["ErrorType"] == "Registration"){

//            }
//            else if (obj["ErrorType"] == "Login"){

//            }
//            else if (obj["ErrorType"] == "message"){

//            }
//            else if (obj["ErrorType"] == ""){ // шаблон

//            }
        }
//        else if(messageType == ""){ // шаблон

//        }
    }

    void onBinaryMessageReceived(){

    }

signals:
    void openChatWindow();

private slots:
    void readMessage(const QString& senderUsername, const QString& message, const QString& timestamp){// мб сменить тип timestamp

    }

private:

};

#endif // RECEIVECOMMAND_H
