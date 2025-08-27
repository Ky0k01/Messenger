#ifndef AUTHWINDOW_H
#define AUTHWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QDebug>

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
    void connections();
    void onLoginClicked();
    void onRegisterClicked();

signals:
    void sendCommand(const QString& commandType, const QVariantMap& map);

private:
    Ui::AuthWindow *ui;
};

#endif // AUTHWINDOW_H
