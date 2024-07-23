#include "rack.h"

Rack::Rack(const int shelvesCount, const double shelfWidth, const int height)
    : shelvesCount(shelvesCount) {
    for (int i = 0; i < shelvesCount; i++) {
        shelves.append(Shelf(shelfWidth, height));
    }
}

Rack::~Rack() {
    for (Shelf& shelf : shelves) {
        shelf.clean();
    }
}

bool Rack::addBook(const Book& book) {
    for (Shelf& shelf : shelves) {
        if (shelf.getBooks().contains(book)) {
            return true;
        }
        if (shelf.getAvailableSpace() >= book.getWidth()) {
            shelf.addBook(book);
            return true;
        }
    }
    return false;
}

void Rack::removeFromRack(const Book &book) {
    for (Shelf& shelf : shelves) {
        if (shelf.getBooks().contains(book)) {
            int index = shelf.getBooks().indexOf(book);
            shelf.removeBook(index);
            return;
        }
    }
}

QVector<Shelf> Rack::getShelves() {
    return shelves;
}

