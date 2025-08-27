#ifndef MEDIATOR_H
#define MEDIATOR_H

#include <QMessageBox>
#include <QDebug>

#include "imediator.h"
#include "AuthorisationWindow/authwindow.h"
#include "ChatWindow/chatwindow.h"
#include "Network/websocketclient.h"
#include "Network/Command/receivecommand.h"
#include "Network/Command/invokecommand.h"

class Mediator : public IMediator{
    Q_OBJECT
public:
    Mediator(QObject *parent = nullptr);
    ~Mediator();

public slots:
    void openChatWindow();

private slots:
    void connections();
    void authorisationWindowConnections();
    void chatWindowConnections();

signals:
    void onConnected();

    void sendLoginRequest(const QString& login, const QString& password);
    void sendRegistrationRequest(const QString& login, const QString& password);

    void sendLoginResult(bool success, const QString& message);
    void sendRegistrationResult(bool success, const QString& message);

    void sendMessage(const QString& message);

private:
    InvokeCommand* invokeCommandManager;
    ReceiveCommand* receiveCommandManager;
    WebSocketClient* socket;
    AuthWindow* authWindow;
    ChatWindow* chatWindow;
    QString url = "ws://localhost:12345";
};

#endif // MEDIATOR_H
