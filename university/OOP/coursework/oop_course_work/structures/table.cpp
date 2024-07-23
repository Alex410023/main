#include "table.h"

#include <algorithm>
#include <random>
#include <ctime>

#include <QDebug>

Table::Table(const int stacksCount)
    : stacksCount(stacksCount) {
    for (int i = 0; i < stacksCount; i++) {
        stacks.append(Stack());
    }
}

Table::~Table() {
    clean();
}

 const QVector<Stack>& Table::getStacks() {
    return stacks;
}

void Table::clean() {
    for (Stack& stack : stacks) {
        stack.clean();
    }
}

void Table::removeFromTable(const Book& book) {
    for (Stack& stack : stacks) {
        if (stack.getBooks().contains(book)) {
            int index = stack.getBooks().indexOf(book);
            stack.removeBook(index);
            return;
        }
    }
}

bool Table::booksGenerated()  {
    for ( Stack& stack : stacks) {
        if (!stack.getBooks().isEmpty()) {
            return true;
        }
    }
    return false;
}

void Table::generateBooks(const int amount, const int W1, const int W2, const int L, const int H) {
    std::default_random_engine generator(std::time(nullptr));

    // Generate 30 books with random thickness
    QVector<Book> books;
    std::uniform_int_distribution<int> distribution(qMin(W1, W2), qMax(W1, W2))/*(W1, W2)*/;
    for (int i = 0; i < amount; i++) {
        int thickness = distribution(generator);
        books.append(Book(L, H, thickness, i));
    }

    // Distribute books randomly
    std::shuffle(books.begin(), books.end(), generator);

    std::uniform_int_distribution<int> stackDistribution(0, stacks.size() - 1);
    for (Book book : books) {
        int stackIndex = stackDistribution(generator);
        stacks[stackIndex].addBook(book);
    }
}

void Table::setWidth(const int width) {
    this->width = width;
}

int Table::getWidth() {
    return width;
}

void Table::addToTable(const Book& book, int stackNumber) {
    int bookIndex = 0;
    for (Stack& stack : stacks) {
        if (stack.getBooks().contains(book)) {
            removeFromTable(book);
            stacks[stackNumber].addBook(book);
            return;
        }
        bookIndex++;
    }

    if (stackNumber == -1) {
        stacks.append(Stack());
        stackNumber = stacks.size() - 1;
        stacks[stackNumber].addBook(book);
    }

    if (stackNumber >= 0 && stackNumber < stacksCount) {
        stacks[stackNumber].addBook(book);
    } else {
        qDebug() << "Invalid stack number";
    }
}
