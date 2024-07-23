#pragma once

#include "book.h"

#include <QVector>

class Stack {
    QVector<Book> books;

public:
    void addBook(const Book& book);
    void removeBook(int index) ;
    void clean();
    int getStackThickness() const;

    QVector<Book> getBooks() const;
};

