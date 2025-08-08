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
}

void AuthWindow::onLoginClicked(){
    QString login = ui->loginEdit->text();
    QString password = ui->PasswordEdit->text();
    emit sendLoginRequest(login, password);
}

void AuthWindow::onRegisterClicked(){
    QString login = ui->loginEdit->text();
    QString password = ui->PasswordEdit->text();
    emit sendRegistrationRequest(login, password);
}

void AuthWindow::onLoginResult(bool success, const QString &errorMessage){
    if (success) {
        qDebug()<<"Login successful!";
        emit openChatWindow();
        // Открыть окно чата
        // Например: ChatWindow *chat = new ChatWindow(login); chat->show(); this->close();
    } else {
        QMessageBox::warning(this, "Login Failed", errorMessage);
    }
}

void AuthWindow::onRegistrationResult(bool success, const QString &errorMessage){
    if (success) {
        QMessageBox::information(this, tr("Registration"), tr("Registration successful!"));
    } else {
        QMessageBox::warning(this, tr("Registration Failed"), errorMessage);
    }
}
