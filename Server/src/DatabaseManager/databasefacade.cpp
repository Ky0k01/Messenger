#include "databasefacade.h"

DatabaseFacade::DatabaseFacade(Logger *logger, QObject *parent): logger(logger), QObject(parent){
    database = QSqlDatabase::addDatabase("QPSQL");

    queryManager = new QueryManager(database, this->logger);
    startupManager = new DatabaseStartupManager(database, this->logger);
}

DatabaseFacade::~DatabaseFacade(){
    delete queryManager;
    delete startupManager;

    database.close();
}


void DatabaseFacade::runDatabase(){
    startupManager->configurateDatabase();
}
