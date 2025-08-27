#include "chatwindow.h"
#include "ui_chatwindow.h"

#include <QPushButton>
#include <QTextEdit>

ChatWindow::ChatWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::ChatWindow){
    ui->setupUi(this);

    ui->Messages->setModel(model);
    ui->Messages->setItemDelegate(delegate);

    connections();
    adjustNessageEditorHeight();
}

ChatWindow::~ChatWindow(){
    delete ui;
}

void ChatWindow::connections(){
    connect(ui->SendBtn, &QPushButton::clicked, this, &ChatWindow::sendButton);
    connect(ui->MessageEditor, &QTextEdit::textChanged, this, &ChatWindow::adjustNessageEditorHeight);
}


void ChatWindow::updateUsersList(){

}

void ChatWindow::sendButton(){
    QString text = ui->MessageEditor->toPlainText().trimmed();

    if(text.isEmpty()){
        return;
    }

    messages<<tr("Me: ")+text;
    model->setStringList(messages);
    ui->MessageEditor->clear();

    QModelIndex lastIndex = model->index(messages.size() - 1);
    ui->Messages->scrollTo(lastIndex);

//    emit sendMessage(text);
}

void ChatWindow::receiveMessage(){

}

void ChatWindow::adjustNessageEditorHeight(){
    QTextDocument *doc = ui->MessageEditor->document();

    doc->setTextWidth(ui->MessageEditor->viewport()->width());
    int docHeight = int(doc->size().height())+6;

    int minHeight = 24;
    int maxHeight = 120;
    int newHeight = qBound(minHeight, docHeight, maxHeight);

    ui->MessageEditor->setFixedHeight(newHeight);
}
