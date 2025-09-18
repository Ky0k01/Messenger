#ifndef MEDIATOR_H
#define MEDIATOR_H

#include "Interface/imediator.h"
#include "Logger/logger.h"

#include "WebSocketManager/websocketfacade.h"
#include "DatabaseManager/databasefacade.h"

class WebSocketManager;

class Mediator : public IMediator{
    Q_OBJECT
public:
    Mediator(Logger* logger, QObject *parent = nullptr);
    ~Mediator();

public slots:
    void runStateMachine();

private slots:
    void connections();
    void setDatabaseFacadeConnections();
    void setWebSocketFacadeConnections();

signals:
    void connectDatabase();

private:
    WebSocketFacade* webSocketFacade;
    DatabaseFacade* databaseFacade;
    Logger *logger;
};

#endif // MEDIATOR_H
