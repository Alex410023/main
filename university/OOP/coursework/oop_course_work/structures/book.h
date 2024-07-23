#pragma once

class Book {
    int width;
    int height;
    int thickness;
    int bookNumber;

public:
    Book(const int width, const int height,
         const int thickness, const int number);

    int getWidth() const;
    int getHeight() const;
    int getThickness() const;
    int getBookNumber() const;

    bool operator==(const Book& other) const;
};
