#pragma once

#include "book.h"

#include <QGraphicsRectItem>
#include <QGraphicsScene>


class BookItem : public QGraphicsRectItem {
    Book book;
    bool isAccessible;

public:
    BookItem(const Book& book, const int xPos, const int yPos,
             const int width, const int height);

    void setOnTop(bool onTop);
    bool getIsAccessible() const;
    const Book& getBook() const;
};

