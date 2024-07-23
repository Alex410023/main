#pragma once

#include "stack.h"

#include <QVector>

class Table {
    QVector<Stack> stacks;
    int stacksCount;
    int width;

public:
    Table(const int stacksCount);
    ~Table();

    void generateBooks(const int amount, const int W1, const int W2,
                       const int L, const int H);
    void clean();

    bool booksGenerated() ;

    void removeFromTable(const Book& book);
    void addToTable(const Book& book, int stackNumber);

    void setWidth(const int width);
    int getWidth();

    const QVector<Stack>& getStacks();
};

