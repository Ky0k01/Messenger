#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include <QObject>
#include <QHash>
#include <QWebSocket>

#include <algorithm>

class SessionManager : public QObject{
    Q_OBJECT
public:
    explicit SessionManager(QObject *parent = nullptr);
    ~SessionManager();

public slots:
    void registerAnonymousSocket(QWebSocket* socket);

    void registerUser(const QString& userId, QWebSocket* socket);

    void deleteUser(const QString& userId);

    void deleteSocket(QWebSocket* socket);

    QWebSocket* getSocketByUserId(const QString& userId) const;

private:
    QHash<QString, QWebSocket*> userSessions;
    QList<QWebSocket*> anonymousSocket;
};

#endif // SESSIONMANAGER_H
