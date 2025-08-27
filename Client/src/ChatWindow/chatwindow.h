#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QMainWindow>
#include <QAbstractListModel>
#include <QStringListModel>

#include <QDateTime>
#include <QShortcut>
#include <QTextDocument>

#include "chatdelegate.h"

#pragma once

namespace Ui {
class ChatWindow;
}

class ChatWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit ChatWindow(QWidget *parent = nullptr);
    ~ChatWindow();

public slots:
    void updateUsersList();
    void sendButton();
    void receiveMessage();

private slots:
    void connections();
    void adjustNessageEditorHeight();

signals:
    void sendMessage(const QString& text);
    void onlineUsersListRequest();

private:
    Ui::ChatWindow *ui;

    QStringList messages;
    QStringListModel* model = new QStringListModel();
    ChatDelegate* delegate = new ChatDelegate;
};

#endif // CHATWINDOW_H
