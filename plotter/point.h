#ifndef POINT_H
#define POINT_H

#include <stdlib.h>
#include <QImage>


class Point
{
public:
    Point() : x(0), y(0) {}
    Point(int x, int y) : x(x), y(y) {}
    Point(const Point& a) : x(a.x), y(a.y) {}

    long long square();
    Point abs();
    void set(int, int);
    void setX(int);
    void setY(int);

    int getX();
    int getY();


    Point operator-(const Point& point) const;
    Point operator+(const Point& point) const;
    long long operator*(const Point& point) const;
    bool operator<(const Point& point) const;
    Point operator>>(int) const;
    bool operator==(const Point& point) const;
    int x;
    int y;

};

#endif // POINT_H
