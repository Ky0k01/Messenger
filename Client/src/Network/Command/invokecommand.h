#ifndef INVOKECOMMAND_H
#define INVOKECOMMAND_H

#include "icommand.h"
#include "jsonfactory.h"
#include "../websocketclient.h"

class SendMessageCommand : public ICommand{
public:
    SendMessageCommand(WebSocketClient* socket, const QString& type, const QVariantMap& data, QObject* parent = nullptr);

    void execute() override;
    void undo() override;

private:
    WebSocketClient* socket;
    QString type;
    QVariantMap data;
};

// пока не реализовано
class SendFileCommand : public ICommand{
public:
    SendFileCommand(WebSocketClient* socket, const QString& type, const QVariantMap& data, QObject* parent = nullptr);

    void execute() override;
    void undo() override;

private:
    WebSocketClient* socket;
};


/*!
 * \brief The InvokeCommand class - класс, который инкапсулирует отправляемые клиентом сообщения и файлы.
 * \param socket - подключенный WebSocket
 */

class InvokeCommand : public QObject{
    Q_OBJECT

public:
    explicit InvokeCommand(WebSocketClient* socket, QObject* parent = nullptr);

public slots:
        void onCommandMessageRequest(const QString& commandType, const QVariantMap& data);
        void onFileMessageRequest();

private:
    WebSocketClient* socket;
};


#endif // INVOKECOMMAND_H
