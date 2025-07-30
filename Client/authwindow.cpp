#include "authwindow.h"
#include "ui_authwindow.h"

#include <QMessageBox>

AuthWindow::AuthWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::AuthWindow){
    ui->setupUi(this);

    initConnections();
}

AuthWindow::~AuthWindow(){
    delete ui;
}

void AuthWindow::initConnections(){
    connect(ui->registerBtn,    &QPushButton::clicked,  this, &AuthWindow::onRegisterClicked);
    connect(ui->loginBtn,       &QPushButton::clicked,  this, &AuthWindow::onLoginClicked);
    connect(ui->serverBtn,      &QPushButton::clicked,  this, &AuthWindow::onServerClicked);

    connect(m_wsClient, &WebSocketClient::loginResult, this, &AuthWindow::onLoginResult);
    connect(m_wsClient, &WebSocketClient::registrationResult, this, &AuthWindow::onRegistrationResult);
}

void AuthWindow::onLoginClicked(){
    QString login = ui->loginEdit->text();
    QString password = ui->PasswordEdit->text();
    m_wsClient->sendLoginRequest(login, password);
}

void AuthWindow::onRegisterClicked(){
    QString login = ui->loginEdit->text();
    QString password = ui->PasswordEdit->text();
    m_wsClient->sendRegisterRequest(login, password);
}

void AuthWindow::onLoginResult(bool success, const QString &errorMessage){
    if (success) {
        qDebug() << "Login successful!";
        // Открыть окно чата
        // Например: ChatWindow *chat = new ChatWindow(login); chat->show(); this->close();
    } else {
        QMessageBox::warning(this, "Login Failed", errorMessage);
    }
}

void AuthWindow::onRegistrationResult(bool success, const QString &errorMessage){
    if (success) {
        QMessageBox::information(this, "Registration", "Registration successful!");
    } else {
        QMessageBox::warning(this, "Registration Failed", errorMessage);
    }
}


void AuthWindow::onServerClicked(){
    m_wsClient = new WebSocketClient(QUrl("ws://localhost:12345"), this);

    if(m_wsClient == nullptr){
        QMessageBox::critical(this, "Error", "Failed to create WebSocket client.");
        return;
    }
    else{
        QMessageBox::information(nullptr, tr("Connected!"), tr("WebSocket client was succesfully created!"));
    }
}
