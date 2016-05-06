#include "point.h"
#include <cmath>




long long Point::square()
{
    return x*x + y*y;
}

Point Point::abs()
{
    return Point(std::abs(x) , std::abs(y));
}

void Point::set(int newx, int newy)
{
    x = newx;
    y = newy;
}


Point Point::operator-(const Point &point) const
{
    return Point(x - point.x, y - point.y);
}

Point Point::operator+(const Point& point) const
{
    return Point(x + point.x, y + point.y);
}

long long Point::operator*(const Point &point) const
{
    return x * point.x + y * point.y;
}

bool Point::operator<(const Point &point) const
{
    return x < point.x && y < point.y;
}

Point Point::operator>>(int n) const
{
    return Point(x >> n, y >> n);
}

bool Point::operator==(const Point &point) const
{
    return  point.x == x && point.y == y;
}

void Point::setY(int y)
{
    this->y = y;
}

int Point::getX()
{
    return x;
}

int Point::getY()
{
    return y;
}

void Point::setX(int x)
{
    this->x = x;
}

