#ifndef POINT_H
#define POINT_H

#include <stdlib.h>
#include <QImage>


class Point
{
public:
    Point() : x(0), y(0), oncurve(true) {}
    Point(int x, int y, bool oncurv) : x(x), y(y), oncurve(oncurv) {}
    Point(const Point& a) : x(a.x), y(a.y), oncurve(a.oncurve) {}

    long long square();
    Point abs();
    void set(int, int);
    void setX(int);
    void setY(int);


    int getX();
    int getY();


    void drawPoint(QImage *pBackBuffer, int x1, int y1, int scale);

    Point operator-(const Point& point) const;
    Point operator+(const Point& point) const;
    long long operator*(const Point& point) const;
    bool operator<(const Point& point) const;
    Point operator>>(int) const;
    bool operator==(const Point& point) const;


    int x;
    int y;

    int xorig;
    int yorig;
    bool oncurve;

};

#endif // POINT_H
