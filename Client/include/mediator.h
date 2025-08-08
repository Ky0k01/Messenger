#ifndef MEDIATOR_H
#define MEDIATOR_H

#include <QMessageBox>
#include <QDebug>

#include "imediator.h"
#include "authwindow.h"
#include "chatwindow.h"
#include "websocketclient.h"

class Mediator : public IMediator{
    Q_OBJECT
public:
    Mediator(QObject *parent = nullptr){
        authWindow = new AuthWindow();
        authWindow->show();
        socket = new WebSocketClient(QUrl("ws://localhost:12345"), this); // позже добавить домен

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
    ~Mediator(){

    }

public slots:
    void openChatWindow(){
        chatWindow = new ChatWindow();
        chatWindow->show();

        authWindow->close();
    }

private slots:
    void connections(){
        qDebug()<<"подключения";
        authorisationWindowConnections();
        chatWindowConnections();
    }

    void authorisationWindowConnections(){
        connect(authWindow, &AuthWindow::sendLoginRequest,              this,       &Mediator::sendLoginRequest);
        connect(this,       &Mediator::sendLoginRequest,                socket,     &WebSocketClient::sendLoginRequest);

        connect(authWindow, &AuthWindow::sendRegistrationRequest,       this,       &Mediator::sendRegistrationRequest);
        connect(this,       &Mediator::sendRegistrationRequest,         socket,     &WebSocketClient::sendRegistrationRequest);

        connect(socket,     &WebSocketClient::sendLoginResult,          this,       &Mediator::sendLoginResult);
        connect(socket,     &WebSocketClient::sendRegistrationResult,   this,       &Mediator::sendRegistrationResult);

        connect(this,       &Mediator::sendLoginResult,                 authWindow, &AuthWindow::onLoginResult);
        connect(this,       &Mediator::sendRegistrationResult,          authWindow, &AuthWindow::onRegistrationResult);

        connect(authWindow, &AuthWindow::openChatWindow,                this,       &Mediator::openChatWindow);
    }

    void chatWindowConnections(){

    }

signals:
    void sendLoginRequest(const QString& login, const QString& password);
    void sendRegistrationRequest(const QString& login, const QString& password);

    void sendLoginResult(bool success, const QString& message);
    void sendRegistrationResult(bool success, const QString& message);

private:
    WebSocketClient* socket;
    AuthWindow* authWindow;
    ChatWindow* chatWindow;
};

#endif // MEDIATOR_H
