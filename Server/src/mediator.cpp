#include "mediator.h"

Mediator::Mediator(Logger *logger, QObject *parent):
    logger(logger), IMediator(parent){
    webSocketFacade = new WebSocketFacade(this->logger, this);
    databaseFacade = new DatabaseFacade(this->logger, this);
    connections();
}

Mediator::~Mediator(){
    delete webSocketFacade;
    delete databaseFacade;
}

void Mediator::runStateMachine(){
    webSocketFacade->runStateMachine();
}

void Mediator::connections(){
    setDatabaseFacadeConnections();
    setWebSocketFacadeConnections();
}

void Mediator::setDatabaseFacadeConnections(){
    connect(this, &Mediator::connectDatabase, databaseFacade, &DatabaseFacade::runDatabase);
}

void Mediator::setWebSocketFacadeConnections(){
    connect(webSocketFacade, &WebSocketFacade::initializeDatabase, this, &Mediator::connectDatabase);
}
