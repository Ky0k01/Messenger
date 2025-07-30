#include <QCoreApplication>
#include <QDir>
#include <QDebug>

#include "server.h"

int main(int argc, char *argv[]){
    QCoreApplication a(argc, argv);

//    QDir pluginsDir(QCoreApplication::applicationDirPath());
//    pluginsDir.cd("sqldrivers");
//    QCoreApplication::addLibraryPath(pluginsDir.path());

//    qDebug()<<QSqlDatabase::drivers()<<" - founded";

    MessengerServer server(12345);

    return a.exec();
}

// #include "main.moc"
