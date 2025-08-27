#ifndef CHATDELEGATE_H
#define CHATDELEGATE_H

#pragma once

#include <QObject>
#include <QStyledItemDelegate>
#include <QPainter>
#include <QTextOption>

class ChatDelegate : public QStyledItemDelegate{
    Q_OBJECT
public:
    explicit ChatDelegate(QObject *parent = nullptr)
        : QStyledItemDelegate(parent){}

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const override;

signals:

};

#endif // CHATDELEGATE_H
