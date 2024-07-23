#include "bookitem.h"

#include <QPen>


BookItem::BookItem(const Book& book, const int xPos, const int yPos,
                   const int width, const int height)
    : QGraphicsRectItem(xPos, yPos, width, height)
    , book(book) {
    setBrush(Qt::lightGray);
    setPen(QPen(Qt::black));

    QGraphicsSimpleTextItem* textItem = new QGraphicsSimpleTextItem(QString::number(book.getBookNumber()));
    textItem->setPos(xPos + 3, yPos);
    textItem->setFont(QFont("Arial", 13));
    textItem->setBrush(Qt::black);

    textItem->setParentItem(this);
}

void BookItem::setOnTop(bool onTop) {
    isAccessible = onTop;
}

const Book& BookItem::getBook() const {
    return book;
}

bool BookItem::getIsAccessible() const {
    return isAccessible;
}
