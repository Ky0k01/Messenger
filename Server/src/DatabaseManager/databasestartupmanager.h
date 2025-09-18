#ifndef STARTUPMANAGER_H
#define STARTUPMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QTextStream>
#include <QDebug>
#include <iostream>

#include "../Logger/logger.h"

using namespace std;

class DatabaseStartupManager : public QObject{
    Q_OBJECT
public:
    explicit DatabaseStartupManager(QSqlDatabase& database, Logger *logger, QObject *parent = nullptr);

public slots:
    void configurateDatabase();

signals:

private slots:
    void setDatabaseSettings(bool testMode);

    void setHostName();
    void setDatabaseName();
    void setUserName();
    void setPassword();
    void printDatabaseSettings();

    void openDatabase();
    void createDatabase();
    void createTables();

private:
    QSqlDatabase& database;
    Logger* logger;

    QString basename;
    string databaseName;
    QString line;
};

#endif // STARTUPMANAGER_H
