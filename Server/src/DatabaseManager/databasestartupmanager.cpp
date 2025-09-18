#include "databasestartupmanager.h"

DatabaseStartupManager::DatabaseStartupManager(QSqlDatabase& database, Logger* logger, QObject *parent):
    database(database), logger(logger), QObject(parent){

}

void DatabaseStartupManager::configurateDatabase(){
    setDatabaseSettings(true);
    openDatabase();
}

void DatabaseStartupManager::setDatabaseSettings(bool testMode){
    if(testMode){
        database.setHostName("localhost");
        database.setDatabaseName("messenger_db");
        database.setUserName("postgres");
        database.setPassword("2905");
    }
    else{
        setHostName();
        setDatabaseName();
        setUserName();
        setPassword();
    }
    printDatabaseSettings();
}

void DatabaseStartupManager::setHostName(){
    string hostName;
    cout<<"Print host name: ";
    cin>>hostName;

    database.setHostName(QString::fromStdString(hostName));
}

void DatabaseStartupManager::setDatabaseName(){
    cout<<"Print database name: ";
    cin>>databaseName;

    basename=QString::fromStdString(databaseName);

    database.setDatabaseName(basename);
}

void DatabaseStartupManager::setUserName(){
    string userName;
    cout<<"Print user name: ";
    cin>>userName;

    database.setUserName(QString::fromStdString(userName));
}

void DatabaseStartupManager::setPassword(){
    string password;
    cout<<"Print password: ";
    cin>>password;

    database.setPassword(QString::fromStdString(password));
}

void DatabaseStartupManager::printDatabaseSettings(){
    qDebug()<<"";
    qDebug()<<database.driverName();
    qDebug()<<database.hostName();
    qDebug()<<database.databaseName();
    qDebug()<<database.userName();
    qDebug()<<database.password();
    qDebug()<<"";

    logger->writeLogLine("QueryManager", database.driverName());
    logger->writeLogLine("QueryManager", database.hostName());
    logger->writeLogLine("QueryManager", database.databaseName());
    logger->writeLogLine("QueryManager", database.userName());
    logger->writeLogLine("QueryManager", database.password());
}

// пересмотреть логику запросов на открытие БД
void DatabaseStartupManager::openDatabase(){
    QString error;
    QTextStream out(stdout);
    out.setCodec("CP866");

    if(!database.open()){
        error = database.lastError().text();
        out<<"Database connection failed:"<<error;
        createDatabase(); // сделать возврат bool
    }
    else{
        qDebug()<<"Database opened";
        qDebug()<<"Initializing tables:";
        createTables();
    }
    qDebug()<<"end of funct open database";
}

void DatabaseStartupManager::createDatabase(){
    QSqlQuery q;
    database.setDatabaseName("postgres");

    if(database.open()){
        if(!q.exec("CREATE DATABASE messenger_db")){
            qDebug()<<"Failed to create database messenger_db";
        }
        else{
            qDebug()<<"created database messenger_db";
            database.setDatabaseName(basename);
            printDatabaseSettings();

            if(database.open()){
                qDebug()<<"opened database messenger_db";
                createTables();
            }
            else{
                qDebug()<<"Failed to open database messenger_db";
            }
        }
    }
    else{
        qDebug()<<"Failed to open database postgres";
    }
}

void DatabaseStartupManager::createTables(){
    QSqlQuery q;
    QString error;
    QTextStream out(stdout);
    out.setCodec("CP866");

    if(!q.exec("CREATE TABLE IF NOT EXISTS users (id BIGSERIAL PRIMARY KEY, "
               "login VARCHAR(64) NOT NULL, "
               "password VARCHAR(128) NOT NULL)")){
        error=q.lastError().text();
        out<<"Failed to create table users: "<<error<<Qt::endl;
    }
    else{
        qDebug()<<"Table users created";
    }

    if(!q.exec("CREATE TABLE IF NOT EXISTS tokens(user_id BIGSERIAL REFERENCES users(id) ON DELETE CASCADE PRIMARY KEY, "
               "token_session VARCHAR NOT NULL, "
               "token_autologin VARCHAR NOT NULL, "
               "token_session_expires_at TIMESTAMP NOT NULL, "
               "token_autologin_expires_at TIMESTAMP NOT NULL)")){
        error=q.lastError().text();
        out<<"Failed to create table tokens: "<<error<<Qt::endl;
    }
    else{
        qDebug()<<"Table tokens created";
    }

    if(!q.exec("CREATE TABLE IF NOT EXISTS messages(message_id BIGSERIAL PRIMARY KEY, "
               "sender_id BIGSERIAL REFERENCES users(id) ON DELETE CASCADE NOT NULL, "
               "receiver_id BIGSERIAL REFERENCES users(id) ON DELETE CASCADE NOT NULL, "
               "content VARCHAR NOT NULL, "
               "sent_at TIMESTAMPTZ NOT NULL)")){
        error=q.lastError().text();
        out<<"Failed to create table messages: "<<error<<Qt::endl;
    }
    else{
        qDebug()<<"Table messages created";
    }
}
