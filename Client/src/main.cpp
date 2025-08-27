/*!
 * \brief Client - клиентская часть учебного проекта Messenger на Qt5 C++17.
 * \author Юденич Максим
 * \version 0.9
 * \date Август 2025
 * \copyright MIT License
 */

#include <QApplication>

#include "mediator.h"

int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    // QTranslator translator;
    // const QStringList uiLanguages = QLocale::system().uiLanguages();
    // for (const QString &locale : uiLanguages) {
    //     const QString baseName = "Client_" + QLocale(locale).name();
    //     if (translator.load(":/i18n/" + baseName)) {
    //         a.installTranslator(&translator);
    //         break;
    //     }
    // }


    Mediator mediator;

    return a.exec();
}
