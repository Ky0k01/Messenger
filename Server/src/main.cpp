#include <QCoreApplication>

#include "Logger/logger.h"
#include "mediator.h"

int main(int argc, char *argv[]){
    QCoreApplication a(argc, argv);

    std::system("chcp 65001");

    Logger logger;
    Mediator mediator(&logger);
    mediator.runStateMachine();

    return a.exec();
}
