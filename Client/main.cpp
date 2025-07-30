// #include "mainwindow.h"

#include <QApplication>
// #include <QLocale>
// #include <QTranslator>

#include "authwindow.h"

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


    AuthWindow authWindow;
    authWindow.show();

    return a.exec();
}
