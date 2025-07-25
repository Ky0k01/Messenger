#ifndef AUTHORISATIONWINDOW_H
#define AUTHORISATIONWINDOW_H

// #pragma once

#include <QWidget>
#include <QMainWindow>

#include "WebSocketClient.h"

namespace Ui {
class AuthorisationWindow;
}

class AuthorisationWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit AuthorisationWindow(QWidget *parent = nullptr);
    ~AuthorisationWindow();

private slots:
    void onRegisterClicked();
    void onLoginClicked();
    void onLoginResult(bool success, const QString &errorMessage);
    void onRegistrationResult(bool success, const QString &errorMessage);

private:
    Ui::AuthorisationWindow *ui;

    void initConnections();

    WebSocketClient *m_wsClient;

};

#endif // AUTHORISATIONWINDOW_H
