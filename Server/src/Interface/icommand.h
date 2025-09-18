#ifndef ICOMMAND_H
#define ICOMMAND_H

#pragma once

#include <QObject>
#include <QDebug>
#include <QVariantMap>

class ICommand : public QObject{
    Q_OBJECT
public:
    explicit ICommand(QObject* parent = nullptr) : QObject(parent){}
    virtual void execute() = 0;
    virtual void undo() = 0;
signals:
    void finished();
};

#endif // ICOMMAND_H
