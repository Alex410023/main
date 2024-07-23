#pragma once

#include "shelf.h"

#include <QVector>

class Rack {
    int shelvesCount;
    QVector<Shelf> shelves;

public:
    Rack(const int shelvesCount, const double shelfWidth, const int height);
    ~Rack();

    void removeFromRack(const Book& book);
    bool addBook(const Book& book);

    QVector<Shelf> getShelves();
};
