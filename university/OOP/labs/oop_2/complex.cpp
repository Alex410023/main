#include "complex.h"

using namespace std;

// TComplex::TComplex()
//     : real(0)
//     , imaginary(0) {}


// TComplex::TComplex(const double re)
//     : real(re)
//     , imaginary(0) {}


TComplex::TComplex(const double re, const double im)
    : real(re)
    , imaginary(im) {}


TComplex::TComplex(const TComplex& other)
    : real(other.real)
    , imaginary(other.imaginary) {}


TComplex::~TComplex() {} // Not needed explicitly as there's no dynamic memory allocation


double TComplex::getReal() const {
    return real;
}


void TComplex::setReal(const double re) {
    real = re;
}


double TComplex::getImaginary() const {
    return imaginary;
}


void TComplex::setImaginary(const double im) {
    imaginary = im;
}


TComplex& TComplex::operator=(const TComplex& complex) {
    if (this == &complex) {
        return *this;
    }
    real = complex.real;
    imaginary = complex.imaginary;
    return *this;
}


bool TComplex::operator==(const TComplex& complex) const {
    return real == complex.real && imaginary == complex.imaginary;
}


TComplex TComplex::operator*(const TComplex& complex) const {
    return TComplex(real * complex.real - imaginary * complex.imaginary,
                    real * complex.imaginary + imaginary * complex.real);
}


TComplex& TComplex::operator+=(const TComplex& complex) {
    real += complex.real;
    imaginary += complex.imaginary;
    return *this;
}


TComplex& TComplex::operator-=(const TComplex& complex) {
    real -= complex.real;
    imaginary -= complex.imaginary;
    return *this;
}


TComplex& TComplex::operator*=(const TComplex& complex) {
    double tempReal = real * complex.real - imaginary * complex.imaginary;
    double tempImaginary = real * complex.imaginary + imaginary * complex.real;
    real = tempReal;
    imaginary = tempImaginary;
    return *this;
}


TComplex& TComplex::operator/=(const TComplex& other) {
    double denominator = other.real * other.real + other.imaginary * other.imaginary;
    double tempReal = (real * other.real + imaginary * other.imaginary) / denominator;
    double tempImaginary = (imaginary * other.real - real * other.imaginary) / denominator;
    real = tempReal;
    imaginary = tempImaginary;
    return *this;
}


ostream& operator<<(ostream& out, const TComplex& complex) {
    if (complex.getReal()) {
        if (complex.getImaginary() > 0) {
            out << complex.getReal() << " + " << complex.getImaginary() << "i";
        } else if (complex.getImaginary() < 0) {
            out << complex.getReal() << " - "<< abs(complex.getImaginary()) << "i";
        } else {
            out << complex.getReal();
        }
    } else {
        if (complex.getImaginary() >= 0) {
            out << complex.getImaginary() << "i";
        } else if (complex.getImaginary() < 0) {
            out << "-"<< abs(complex.getImaginary()) << "i";
        }
    }

    return out;
}


istream& operator>>(istream& in, TComplex& complex) {
    double re, im;
    in >> re >> im;

    complex.setReal(re);
    complex.setImaginary(im);

    return in;
}
