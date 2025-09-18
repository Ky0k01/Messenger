#ifndef WEBSOCKETFACADE_H
#define WEBSOCKETFACADE_H

#include <QObject>

#include "websocketstartupmanager.h"
#include "websocketmanager.h"
#include "Command/invokecommand.h"
#include "Command/receivecommand.h"


class WebSocketFacade : public QObject{
    Q_OBJECT
public:
    explicit WebSocketFacade(Logger* logger, QObject *parent = nullptr);
    ~WebSocketFacade();

public slots:
    void runStateMachine();

signals:
    void initializeDatabase();

private slots:
    void setConnections();

    void processStateMachine(int currentState);

    void startServer();
    void setPort();


private:
    QWebSocketServer* server;

    Logger* logger;
    WebSocketStartupManager* webSocketStartupManager;
    SessionManager* sessionManager;
    WebSocketManager* socketManager;
    InvokeCommandManager* invokeCommandManager;
    ReceiveCommandManager* receiveCommandManager;

    enum States{
        START_STATE,
        CHECK_UPDATE_STATE,
        UPDATING_STATE,
        CONFIGURATION_STATE,
        READY_STATE
    };
};

#endif // WEBSOCKETFACADE_H
