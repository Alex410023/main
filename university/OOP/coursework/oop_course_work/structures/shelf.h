#pragma once

#include "book.h"

#include <QVector>

class Shelf {
    int width;
    int height;
    QVector<Book> books;

public:
    Shelf(const int width,  int height);
    ~Shelf();

    void addBook(const Book& book);
    bool isFull() const;
    int getAvailableSpace() const;
    int getWidth() const;
    int getHeight() const;

    void removeBook(int index);
    void clean();

    QVector<Book> getBooks() const;
};


