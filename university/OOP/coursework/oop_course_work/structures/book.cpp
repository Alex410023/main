#include "book.h"

Book::Book(const int width, const int height,
           const int thickness, const int number)
    : width(width)
    , height(height)
    , thickness(thickness)
    , bookNumber(number) {}


int Book::getWidth() const {
    return width;
}

int Book::getHeight() const {
    return height;
}

int Book::getThickness() const {
    return thickness;
}

int Book::getBookNumber() const {
    return bookNumber;
}

bool Book::operator==(const Book& other) const {
    return width == other.width &&
           height == other.height &&
           thickness == other.thickness &&
           bookNumber == other.bookNumber;
}
