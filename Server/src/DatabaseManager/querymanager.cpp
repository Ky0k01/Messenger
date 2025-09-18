#include "querymanager.h"


QueryManager::QueryManager(QSqlDatabase &database, Logger *logger, QObject *parent):
    database(database), logger(logger), QObject(parent){

}

