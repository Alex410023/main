#include "rational.h"

TRational::TRational(const int num, const int denom)
    : num(num)
    , denom(denom) {
    reduce();
}

TRational::TRational(const TRational& rational)
    : num(rational.getNum())
    , denom(rational.getDenom()) {}

TRational::~TRational() {} // Not needed explicitly as there's no dynamic memory allocation

int TRational::getNum() const {
    return num;
}

void TRational::setNum(const int num) {
    this->num = num;
}

int TRational::getDenom() const {
    return denom;
}

void TRational::setDenom(const int denom) {
    this->denom = denom;
}

int TRational::gcd(const int a, const int b) const {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

void TRational::reduce() {
    int d = gcd(num, denom);
    num /= d;
    denom /= d;

    if (denom < 0) {
        num *= -1;
        denom *= -1;
    }
}

bool TRational::operator==(const TRational& rational) const {
    return num == rational.num &&
           denom == rational.denom;
}


TRational TRational::operator*(const TRational& rational) const {
    return TRational(num * rational.num,
                     denom * rational.denom);
}

TRational& TRational::operator+=(const TRational& rational) {
    int tempNum = num * rational.denom + rational.num * denom;
    int tempDenom = denom * rational.denom;
    num = tempNum;
    denom = tempDenom;
    reduce();
    return *this;
}

TRational& TRational::operator-=(const TRational& rational) {
    int tempNum = num * rational.denom - rational.num * denom;
    int tempDenom = denom * rational.denom;
    num = tempNum;
    denom = tempDenom;
    reduce();
    return *this;
}

TRational& TRational::operator*=(const TRational& rational) {
    num *= rational.num;
    denom *= rational.denom;
    reduce();
    return *this;
}

TRational& TRational::operator/=(const TRational& rational) {
    num *= rational.denom;
    denom *= rational.num;
    reduce();
    return *this;
}

std::ostream& operator<<(std::ostream& out, const TRational& rational) {
    if (rational.getDenom() == 0) {
        out << "NaN";
    } else {
        if (rational.getNum()) {
            if (rational.getDenom() == 1) {
                out << rational.getNum();
            } else {
                out << rational.getNum() << " / " << rational.getDenom();
            }
        } else {
            out << 0;
        }
    }
    return out;
}

std::istream& operator>>(std::istream& in, TRational& rational) {
    int num, denom;
    in >> num >> denom;

    rational.setNum(num);
    rational.setDenom(denom);

    return in;
}

QString& operator<<(QString& out, const TRational& rational) {
    if (rational.getDenom() == 0) {
        out += "NaN";
    } else {
        out += QString().setNum(rational.getNum());

        if (rational.getNum() && rational.getDenom() != 1) {
            out += "/";
            out += QString().setNum(rational.getDenom());
        }
    }

    return out;
}

