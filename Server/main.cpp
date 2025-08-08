#include <QCoreApplication>
#include <QDir>

#include "server.h"

int main(int argc, char *argv[]){
    QCoreApplication a(argc, argv);

    Server server(12345);

    return a.exec();
}
