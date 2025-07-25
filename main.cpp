#include <QCoreApplication>
#include <QDir>

#include "server.h"

int main(int argc, char *argv[]){
    QCoreApplication a(argc, argv);

    QDir pluginsDir(QCoreApplication::applicationDirPath());
    pluginsDir.cd("sqldrivers");  // Для Windows/Linux
    QCoreApplication::addLibraryPath(pluginsDir.path());

    MessengerServer server(12345); // Change port as needed

    return a.exec();
}

// #include "main.moc"
