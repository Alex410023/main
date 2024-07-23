#include "shelf.h"

Shelf::Shelf( int width,  int height)
    : width(width)
    , height(height) {}

Shelf::~Shelf() {
    clean();
}

void Shelf::addBook(const Book& book) {
    books.append(book);
}

void Shelf::clean() {
    books.clear();
}

void Shelf::removeBook(int index) {
    books.takeAt(index);
}

bool Shelf::isFull() const {
    int totalWidth = 0;
    for (const Book& book : books) {
        totalWidth += book.getWidth();
    }
    return totalWidth >= width;
}

int Shelf::getAvailableSpace() const {
    int totalWidth = 0;
    for (const Book& book : books) {
        totalWidth += book.getWidth();
    }
    return width - totalWidth;
}

int Shelf::getWidth() const {
    return width;
}

int Shelf::getHeight() const {
    return height;
}

QVector<Book> Shelf::getBooks() const {
    return books;
}
