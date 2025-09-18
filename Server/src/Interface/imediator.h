#ifndef IMEDIATOR_H
#define IMEDIATOR_H

#pragma once

#include <QObject>
#include <QVariant>

class IMediator : public QObject{
public:
    explicit IMediator(QObject* parent = nullptr) : QObject(parent){}
    virtual ~IMediator() = default;
};

#endif // IMEDIATOR_H
