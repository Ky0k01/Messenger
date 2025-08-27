#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H

#include <QObject>
#include <QWebSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSslCertificate>
#include <QUuid>
#include <QTimer>

#include "Command/receivecommand.h"

class WebSocketClient : public QObject{
    Q_OBJECT
public:
    explicit WebSocketClient(ReceiveCommand *receiveCommandManager, const QUrl &url, QObject *parent = nullptr);
    ~WebSocketClient();

    void sendTextMessage(const QJsonObject& obj){
        socket.sendTextMessage(QJsonDocument(obj).toJson(QJsonDocument::Compact));
        qDebug()<<"Message sent: "<<QJsonDocument(obj).toJson(QJsonDocument::Compact); // добавить больше полей из obj
    }

    void sendBinaryMessage(const QByteArray& file){
        socket.sendBinaryMessage(file);
        qDebug()<<"File sent: "<<file.size();
    }

signals:
    void sendReceivedMessage(const QJsonObject& obj);
    void sendReceivedFile(/*QFile ?*/);

private slots:
    void connections();
    void onConnected();
    void sendPing();
    void onPongReceived(quint64 elapsedTime, const QByteArray &payLoad);

    void onTextMessageReceived(const QString &message){ // мб переименовать
        QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
        QJsonObject obj = doc.object();

        receiveCommandManager->onTextMessageReceived(obj);
    }

    void onBinaryMessageReceived(const QByteArray& message){ // мб переименовать
        // преобразовать файлы в байты
//        emit sendReceivedFile();
    }

private:
    ReceiveCommand* receiveCommandManager;
    QWebSocket socket;
    QUrl url;
    QTimer pingTimer;
};

#endif // WEBSOCKETCLIENT_H
