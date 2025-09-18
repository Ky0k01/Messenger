#ifndef DATABASEFACADE_H
#define DATABASEFACADE_H

#include <QObject>

#include "querymanager.h"
#include "databasestartupmanager.h"

class DatabaseFacade : public QObject{
    Q_OBJECT
public:
    explicit DatabaseFacade(Logger *logger, QObject *parent = nullptr);
    ~DatabaseFacade();

public slots:
    void runDatabase();

signals:

private:
    // добавить менеджер миграций
    QSqlDatabase database;
    DatabaseStartupManager* startupManager;
    QueryManager* queryManager;
    Logger* logger;


};

#endif // DATABASEFACADE_H
