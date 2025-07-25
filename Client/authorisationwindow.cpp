#include "authorisationwindow.h"
#include "ui_authorisationwindow.h"

#include <QUrl>
#include <QMessageBox>

AuthorisationWindow::AuthorisationWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::AuthorisationWindow){
    ui->setupUi(this);

    initConnections();

     m_wsClient = new WebSocketClient(QUrl("ws://localhost:1234"), this);
}

AuthorisationWindow::~AuthorisationWindow(){
    delete ui;
}

void AuthorisationWindow::initConnections(){
    connect(ui->registerBtn, &QPushButton::clicked, this, &AuthorisationWindow::onRegisterClicked);
    connect(ui->loginBtn, &QPushButton::clicked, this, &AuthorisationWindow::onLoginClicked);

    connect(m_wsClient, &WebSocketClient::loginResult, this, &AuthorisationWindow::onLoginResult);
    connect(m_wsClient, &WebSocketClient::registrationResult, this, &AuthorisationWindow::onRegistrationResult);
}

void AuthorisationWindow::onLoginClicked(){
    QString login = ui->loginEdit->text();
    QString password = ui->PasswordEdit->text();
    m_wsClient->sendLoginRequest(login, password);
}

void AuthorisationWindow::onRegisterClicked(){
    QString login = ui->loginEdit->text();
    QString password = ui->PasswordEdit->text();
    m_wsClient->sendRegisterRequest(login, password);
}

void AuthorisationWindow::onLoginResult(bool success, const QString &errorMessage){
    if (success) {
        // Открыть окно чата
        // Например: ChatWindow *chat = new ChatWindow(login); chat->show(); this->close();
    } else {
        QMessageBox::warning(this, "Login Failed", errorMessage);
    }
}

void AuthorisationWindow::onRegistrationResult(bool success, const QString &errorMessage){
    if (success) {
        QMessageBox::information(this, "Registration", "Registration successful!");
    } else {
        QMessageBox::warning(this, "Registration Failed", errorMessage);
    }
}

// void AuthorisationWindow::onRememberMeClicked(){
//     // Handle "Remember Me" logic here
// }
