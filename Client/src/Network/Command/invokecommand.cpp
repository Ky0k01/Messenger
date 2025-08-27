#include "invokecommand.h"

InvokeCommand::InvokeCommand(WebSocketClient *socket, QObject *parent)
    : QObject(parent), socket(socket){}

void InvokeCommand::onCommandMessageRequest(const QString &commandType, const QVariantMap &data){
    qDebug()<<"[InvokeCommand] request message type -"<<commandType;
    ICommand* cmd = nullptr;

    cmd = new SendMessageCommand(socket, commandType, data);

    if(cmd){
        connect(cmd, &ICommand::finished, cmd, &ICommand::deleteLater);
        cmd->execute();
    }
}

void InvokeCommand::onFileMessageRequest(){

}


SendMessageCommand::SendMessageCommand(WebSocketClient *socket, const QString &type, const QVariantMap &data, QObject *parent) :
    ICommand(parent), socket(socket), type(type), data(data){}

void SendMessageCommand::execute(){
    QJsonObject obj = JsonFactory::create(type, data);
    socket->sendTextMessage(obj);
    emit finished();
}

void SendMessageCommand::undo(){

}


SendFileCommand::SendFileCommand(WebSocketClient *socket, const QString &type, const QVariantMap &data, QObject *parent) :
    ICommand(parent), socket(socket){}

void SendFileCommand::execute(){
    // отправка файла в сокет
    emit finished();
}

void SendFileCommand::undo(){

}
