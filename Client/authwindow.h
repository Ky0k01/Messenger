#ifndef AUTHWINDOW_H
#define AUTHWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class AuthWindow;
}
QT_END_NAMESPACE

class AuthWindow : public QMainWindow{
    Q_OBJECT
public:
    explicit AuthWindow(QWidget *parent = nullptr);
    ~AuthWindow();

private slots:
    void onLoginClicked();
    void onRegisterClicked();

    void onLoginResult(bool success, const QString &errorMessage);
    void onRegistrationResult(bool success, const QString &errorMessage);

signals:
    void sendLoginRequest(const QString& login, const QString& password);
    void sendRegistrationRequest(const QString& login, const QString& password);
    void openChatWindow();

private:
    Ui::AuthWindow *ui;
    void initConnections();
};

#endif // AUTHWINDOW_H
