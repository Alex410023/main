#pragma once

#include <iostream>
#include <QString>

class TComplex {
private:
    double real;
    double imaginary;

public:
    TComplex(const double re = 0.0, const double im = 0.0);
    TComplex(const TComplex& other);
    TComplex(const QByteArray& arr);

    double getReal() const;
    void setReal(const double re);
    double getImaginary() const;
    void setImaginary(const double im);

    TComplex& operator=(const TComplex& complex);

    bool operator==(const TComplex& complex) const;

    TComplex operator*(const TComplex& complex) const;
    TComplex operator-(const TComplex& complex) const;
    TComplex operator/(const TComplex& complex) const;

    TComplex& operator+=(const TComplex& complex);
    TComplex& operator-=(const TComplex& complex);
    TComplex& operator*=(const TComplex& complex);
    TComplex& operator/=(const TComplex& complex);

    friend std::ostream& operator<<(std::ostream& out, const TComplex& complex);
    friend std::istream& operator>>(std::istream& in, TComplex& complex);

    friend QString& operator<<(QString& out, const TComplex& complex);

    friend QByteArray& operator>>(QByteArray& arr, TComplex& complex);
    operator QString ();
};
