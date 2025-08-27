#include "chatdelegate.h"
#include <QPainter>
#include <QFontMetrics>

void ChatDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                         const QModelIndex &index) const {
    painter->save();

    QString text = index.data().toString();

    // Фон выделения, остальное — фон системы
    if (option.state & QStyle::State_Selected) {
        painter->fillRect(option.rect, option.palette.highlight());
    }

    // Определяем префикс и цвет
    QString prefix;
    QColor prefixColor;
    QRegularExpression re("^([^:]+:)");
    QRegularExpressionMatch match = re.match(text);
    if (match.hasMatch()) {
        prefix = match.captured(1);
        prefixColor = (prefix == "Me:") ? Qt::blue : Qt::red;
    }
    QString restText = text.mid(prefix.length()).trimmed();

    // Отступы
    QRect textRect = option.rect.adjusted(8, 4, -8, -4);

    QFont font = option.font;
    painter->setFont(font);
    QFontMetrics fm(font);

    int prefixWidth = !prefix.isEmpty() ? fm.horizontalAdvance(prefix + " ") : 0;
    int availableWidth = textRect.width() - prefixWidth;

    int x = textRect.left();

    // Рисуем префикс
    if (!prefix.isEmpty()) {
        painter->setPen(prefixColor);
        painter->drawText(QRect(x, textRect.top(), prefixWidth, textRect.height()),
                          Qt::AlignLeft | Qt::AlignTop, prefix);
        x += prefixWidth;
    }

    // Рисуем текст сообщения с переносом строк
    painter->setPen((option.state & QStyle::State_Selected) ? option.palette.highlightedText().color() : Qt::black);
    QRect restTextRect(x, textRect.top(), availableWidth, textRect.height());
    painter->drawText(restTextRect, Qt::AlignLeft | Qt::AlignTop | Qt::TextWordWrap, restText);

    painter->restore();
}

QSize ChatDelegate::sizeHint(const QStyleOptionViewItem &option,
                             const QModelIndex &index) const {
    QString text = index.data().toString();
    QFont font = option.font;
    QFontMetrics fm(font);

    QString prefix;
    QRegularExpression re("^([^:]+:)");
    QRegularExpressionMatch match = re.match(text);
    if (match.hasMatch()) {
        prefix = match.captured(1);
    }
    QString restText = text.mid(prefix.length()).trimmed();

    int width = option.rect.width() > 0 ? option.rect.width() - 16 : 300;
    int prefixWidth = !prefix.isEmpty() ? fm.horizontalAdvance(prefix + " ") : 0;
    int textWidth = width - prefixWidth;

    // boundingRect учитывает переносы текста
    QRect restTextBounding = fm.boundingRect(0, 0, textWidth, 10000, Qt::TextWordWrap, restText);
    int height = qMax(fm.height(), restTextBounding.height()) + 8;

    return QSize(option.rect.width(), height);
}
