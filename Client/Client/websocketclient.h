#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H

// #pragma once

#include <QObject>
#include <QtWebSockets/QWebSocket>

class WebSocketClient : public QObject
{
    Q_OBJECT
public:
    explicit WebSocketClient(const QUrl &url, QObject *parent = nullptr);

    void sendLoginRequest(const QString &login, const QString &password);
    void sendRegisterRequest(const QString &login, const QString &password);

signals:
    void loginResult(bool success, const QString &errorMessage);
    void registrationResult(bool success, const QString &errorMessage);

private slots:
    void onConnected();
    void onTextMessageReceived(const QString &message);

private:
    QWebSocket m_webSocket;
    QUrl m_url;
};

#endif // WEBSOCKETCLIENT_H
