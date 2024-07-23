#pragma once

#include <iostream>
#include <QString>

class TRational {
private:
    int num;
    int denom;

public:
    TRational(const int num = 0, const int denom = 1);
    TRational(const TRational& rational);
    ~TRational();

    int getNum() const;
    void setNum(const int num);
    int getDenom() const;
    void setDenom(const int denom);

    int gcd(const int a, const int b) const;
    void reduce();

    bool operator==(const TRational& rational) const;

    TRational operator*(const TRational& rational) const;

    TRational& operator+=(const TRational& rational);
    TRational& operator-=(const TRational& rational);
    TRational& operator*=(const TRational& rational);
    TRational& operator/=(const TRational& rational);

    friend std::ostream& operator<<(std::ostream& out, const TRational& rational);
    friend std::istream& operator>>(std::istream& in, TRational& rational);
    friend QString& operator<<(QString& out, const TRational& rational);
};
