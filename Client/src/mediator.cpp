#include "mediator.h"

Mediator::Mediator(QObject *parent){
    authWindow = new AuthWindow();
    authWindow->show();

    receiveCommandManager = new ReceiveCommand();
    socket = new WebSocketClient(receiveCommandManager, QUrl(url), this); // позже добавить домен
    invokeCommandManager = new InvokeCommand(socket);

    connections();

    if(socket == nullptr){
        QMessageBox::critical(nullptr, tr("Error"), tr("Failed to create WebSocket client."));
        return;
    }
    else{

        QMessageBox::information(nullptr, tr("Connected!"), tr("WebSocket client was succesfully created!"));
        // сделать таймер на автоподключение
    }
}

Mediator::~Mediator(){

}

void Mediator::openChatWindow(){
    chatWindow = new ChatWindow();
    chatWindow->show();

    authWindow->close();
}

void Mediator::connections(){
    authorisationWindowConnections();
    chatWindowConnections();
}

void Mediator::authorisationWindowConnections(){
    connect(authWindow, &AuthWindow::sendCommand, invokeCommandManager, &InvokeCommand::onCommandMessageRequest);
    connect(receiveCommandManager, &ReceiveCommand::openChatWindow, this, &Mediator::openChatWindow);
}

void Mediator::chatWindowConnections(){
    //        connect(chatWindow, &ChatWindow::sendMessage,   this,   &Mediator::sendMessage);
    //        connect(this,       &Mediator::sendMessage,     socket, &WebSocketClient::sendMessage);
}
