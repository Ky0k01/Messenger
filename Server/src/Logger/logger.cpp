#include "logger.h"

Logger::Logger(QObject *parent) : QObject(parent){
    startLogger();
}

Logger::~Logger(){
    if(logFile.isOpen()){
        logFile.close();
    }
}


bool Logger::checkWorkingState(){
    if(!dir.exists("Logs")){
        return false;
    }
    else if(!logFile.isOpen()){
        return false;
    }
    else{
        return true;
    }
}

void Logger::startLogger(){
    if(!dir.exists("Logs")) dir.mkdir("Logs");

    dir.setCurrent(QCoreApplication::applicationDirPath()+"/Logs");

    logFile.setFileName(QDate::currentDate().toString("dd.MM.yyyy")+"_"+QTime::currentTime().toString("hh.mm.ss")+".log");

    if(!logFile.open(QIODevice::ReadWrite | QIODevice::Text)){
        writeLogLine("Logger", "Failed to open log file", "Error");
    }
    else{
        writeLogLine("Logger", "Logger start working");
    }
}

void Logger::writeLogLine(const QString &module, const QString &line, const QString &error){
    if(!logFile.isOpen()) startLogger();

    QTextStream out(&logFile);

    out<<QDate::currentDate().toString("dd.MM.yyyy")<<" "<<QTime::currentTime().toString("hh.mm.ss")<<" "<<"["<<module<<"] "<<
         ((error == "") ? error : "["+error+"]")<<" "
      <<line<<Qt::endl;
}

void Logger::printTerminal(const QString& module, const QString& message){
    cout<<message.toStdString()<<endl;

    writeLogLine(module, message);
}

QString Logger::printTerminalAndReturnInput(const QString& module, const string& message){
    string text;
    QTextStream logOut(&logFile);

    cout<<message;
    cin>>text;

    writeLogLine(module, QString::fromStdString(message+text));

    return QString::fromStdString(text);
}
