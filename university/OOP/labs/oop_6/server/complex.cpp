#include "complex.h"

#include <QStringList>

using namespace std;

TComplex::TComplex(const double re, const double im)
    : real(re)
    , imaginary(im) {}


TComplex::TComplex(const TComplex& other)
    : real(other.real)
    , imaginary(other.imaginary) {}


TComplex::TComplex(const QByteArray &arr) {
    QString str = QString(arr);
    QStringList substrings = str.split(',');

    double re = substrings.at(0).toDouble();
    real = re;

    double im = substrings.at(1).toDouble();
    imaginary = im;
}

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

TComplex TComplex::operator-(const TComplex& complex) const {
    return TComplex(real - complex.real,
                    imaginary - complex.imaginary);
}

TComplex TComplex::operator/(const TComplex& complex) const {
    double denominator = complex.real * complex.real + complex.imaginary * complex.imaginary;
    double tempReal = (real * complex.real + imaginary * complex.imaginary) / denominator;
    double tempImaginary = (imaginary * complex.real - real * complex.imaginary) / denominator;
    return TComplex(tempReal, tempImaginary);
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


TComplex& TComplex::operator/=(const TComplex& complex) {
    double denominator = complex.real * complex.real + complex.imaginary * complex.imaginary;
    double tempReal = (real * complex.real + imaginary * complex.imaginary) / denominator;
    double tempImaginary = (imaginary * complex.real - real * complex.imaginary) / denominator;
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

QString& operator<<(QString& out, const TComplex& complex) {
    if (complex.getReal()) {
        out += QString().setNum(complex.getReal());
    }
    if (complex.getImaginary()) {
        if (complex.getImaginary() > 0) {
            out += "+";
            out += QString().setNum(complex.getImaginary());
        } else {
            out += "-";
            out += QString().setNum(abs(complex.getImaginary()));
        }
        out += "i";
    }

    return out;
}

QByteArray& operator>>(QByteArray& arr, TComplex& complex) {
    int index = arr.indexOf(';');
    complex = TComplex(arr.left(index));
    arr = arr.mid(index + 1);

    return arr;
}

TComplex::operator QString () {
    QString str = "";
    str += QString().setNum(real);
    str += (imaginary >= 0) ? ("+") : ("-");
    str += QString().setNum(imaginary);
    str += "";

    return str;
}

