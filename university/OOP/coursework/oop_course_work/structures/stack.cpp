#include "stack.h"

void Stack::addBook(const Book& book) {
    books.append(book);
}

void Stack::removeBook(int index)  {
    books.takeAt(index);
}

void Stack::clean() {
    books.clear();
}

QVector<Book> Stack::getBooks() const {
    return books;
}

int Stack::getStackThickness() const {
    int height = 0;
    for (const Book& book : books) {
        height += book.getThickness();
    }
    return height;
}
