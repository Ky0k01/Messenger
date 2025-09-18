#ifndef LOGGER_H
#define LOGGER_H

#include <QCoreApplication>
#include <QObject>
#include <QFile>
#include <QDir>
#include <QTime>
#include <QDebug>
#include <QDate>

#include <iostream>
#include <string>

using namespace std;

class Logger : public QObject{
    Q_OBJECT
public:
    explicit Logger(QObject* parent = nullptr);
    ~Logger();

public slots:
    bool checkWorkingState();

    void startLogger();

    void writeLogLine(const QString& module, const QString& line, const QString& error = "");

    void printTerminal(const QString &module, const QString &message);

    QString printTerminalAndReturnInput(const QString& module, const std::string& message);

private:
    QFile logFile;
    QDir dir = QCoreApplication::applicationDirPath();
};

#endif // LOGGER_H
