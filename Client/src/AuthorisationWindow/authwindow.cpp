#include "authwindow.h"
#include "ui_authwindow.h"

#include <QMessageBox>

AuthWindow::AuthWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::AuthWindow){
    ui->setupUi(this);
    connections();
}

AuthWindow::~AuthWindow(){
    delete ui;
}

void AuthWindow::connections(){
    connect(ui->loginBtn,       &QPushButton::clicked,  this, &AuthWindow::onLoginClicked);
    connect(ui->registerBtn,    &QPushButton::clicked,  this, &AuthWindow::onRegisterClicked);
}

void AuthWindow::onLoginClicked(){
    QString login = ui->loginEdit->text();
    QString password = ui->PasswordEdit->text();
    ui->PasswordEdit->clear();

    QVariantMap map;
    map.insert("login", login);
    map.insert("password", password);

    emit sendCommand("Login", map);
//    emit sendLoginRequest(login, password);
}

void AuthWindow::onRegisterClicked(){
    QString login = ui->loginEdit->text();
    QString password = ui->PasswordEdit->text();

    QVariantMap map;
    map.insert("login", login);
    map.insert("password", password);

    ui->loginEdit->clear();
    ui->PasswordEdit->clear();

    emit sendCommand("Registration", map);
}
