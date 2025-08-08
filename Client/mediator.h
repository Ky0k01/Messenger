#ifndef MEDIATOR_H
#define MEDIATOR_H

#include <QMessageBox>
#include <QDebug>

#include "imediator.h"
#include "authwindow.h"
#include "websocketclient.h"

class Mediator : public IMediator{
    Q_OBJECT
public:
    Mediator(QObject *parent = nullptr){
        connections();

        authWindow = new AuthWindow();
        authWindow->show();

        socket = new WebSocketClient(QUrl("ws://localhost:12345"), this); // позже добавить домен

        if(socket == nullptr){
            QMessageBox::critical(nullptr, tr("Error"), tr("Failed to create WebSocket client."));
            return;
        }
        else{
            QMessageBox::information(nullptr, tr("Connected!"), tr("WebSocket client was succesfully created!"));
            // сделать таймер на автоподключение
        }
    }
    ~Mediator(){}

public slots:

signals:
    void sendRegistrationRequest(const QString& login, const QString& password);
    void sendLoginRequest(const QString& login, const QString& password);

    void sendLoginResult(bool success, const QString& message);
    void sendRegistrationResult(bool success, const QString& message);


private:
    void connections(){
        connect(authWindow, &AuthWindow::sendLoginRequest,              this,   &Mediator::sendLoginRequest);
        connect(this,       &Mediator::sendLoginRequest,                socket, &WebSocketClient::sendLoginRequest);

        connect(authWindow, &AuthWindow::sendRegistrationRequest,       this,   &Mediator::sendRegistrationRequest);
        connect(this,       &Mediator::sendRegistrationRequest,         socket, &WebSocketClient::sendRegistrationRequest);

        connect(socket,     &WebSocketClient::sendLoginResult,          this,   &Mediator::sendLoginResult);
        connect(socket,     &WebSocketClient::sendRegistrationResult,   this,   &Mediator::sendRegistrationResult);

    }

    WebSocketClient* socket;
    AuthWindow* authWindow;
};

#endif // MEDIATOR_H
