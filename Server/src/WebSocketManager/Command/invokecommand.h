#ifndef INVOKECOMMAND_H
#define INVOKECOMMAND_H

#include <QObject>

#include "../../Interface/icommand.h"

class InvokeCommandManager : public QObject{
    Q_OBJECT
public:
    explicit InvokeCommandManager(QObject *parent = nullptr);

signals:

};

#endif // INVOKECOMMAND_H
