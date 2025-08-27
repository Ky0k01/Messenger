#ifndef JSONFACTORY_H
#define JSONFACTORY_H

#pragma once

#include <QString>
#include <QVariantMap>
#include <QJsonObject>

class JsonFactory{
public:
    static QJsonObject create(const QString& type, const QVariantMap& params);
};

#endif // JSONFACTORY_H
