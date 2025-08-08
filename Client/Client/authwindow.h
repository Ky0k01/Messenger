#ifndef AUTHWINDOW_H
#define AUTHWINDOW_H

// #pragma once

#include <QMainWindow>

#include "websocketclient.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class AuthWindow;
}
QT_END_NAMESPACE

class AuthWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AuthWindow(QWidget *parent = nullptr);
    ~AuthWindow();

private slots:
    void onRegisterClicked();
    void onLoginClicked();
    void onServerClicked();

    void onLoginResult(bool success, const QString &errorMessage);
    void onRegistrationResult(bool success, const QString &errorMessage);

private:
    Ui::AuthWindow *ui;

    void initConnections();
    WebSocketClient *m_wsClient;
};

#endif // AUTHWINDOW_H
