#ifndef SERVER_H
#define SERVER_H

#include <QWebSocketServer>
#include <QWebSocket>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include <QJsonDocument>
#include <QJsonObject>

#include <QCryptographicHash>
#include <QSslCertificate>

#include <QFile>

class Server : public QObject{
    Q_OBJECT

public:
    Server(quint16 port, QObject *parent = nullptr);

public slots:
    void onNewConnection();
    void textMessageReceived(const QString& message);
    void binaryMessageReceived(const QByteArray& message);

    void onPongReceived(quint64 elapsedTime, const QByteArray& payLoad);

private slots:
    void readSaltFile();

private:
    QWebSocketServer *server;
    QSqlDatabase db;

    QString salt;

    QCryptographicHash* hash = new QCryptographicHash(QCryptographicHash::RealSha3_512);
};

#endif // SERVER_H
