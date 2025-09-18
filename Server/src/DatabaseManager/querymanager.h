#ifndef QUERYMANAGER_H
#define QUERYMANAGER_H

#include <QObject>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include <QSocketNotifier>
#include <QTextStream>
#include <QDebug>
#include <iostream>

#include "../Logger/logger.h"

using namespace std;

class QueryManager : public QObject{
    Q_OBJECT
public:
    explicit QueryManager(QSqlDatabase& database, Logger* logger, QObject *parent = nullptr);

public slots:

signals:

private:
    QSqlDatabase& database;
    Logger *logger;
};

#endif // QUERYMANAGER_H
