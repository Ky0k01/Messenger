#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H

#include <QObject>
#include <QWebSocket>
#include <QJsonDocument>
#include <QJsonObject>

class WebSocketClient : public QObject{
    Q_OBJECT
public:
    explicit WebSocketClient(const QUrl &url, QObject *parent = nullptr);
    ~WebSocketClient();

    void sendLoginRequest(const QString &login, const QString &password);
    void sendRegistrationRequest(const QString &login, const QString &password);

signals:
    void sendLoginResult(bool success, const QString &errorMessage);
    void sendRegistrationResult(bool success, const QString &errorMessage);

private slots:
    void onConnected();
    void onTextMessageReceived(const QString& message);
    void onBinaryMessageReceived(const QByteArray& message);

private:
    QWebSocket m_webSocket;
    QUrl m_url;
};

#endif // WEBSOCKETCLIENT_H
