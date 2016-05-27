#include "point.h"
#include <cmath>




long long Point::square()
{
    return x*x + y*y;
}

Point Point::abs()
{
    return Point(std::abs(x) , std::abs(y), true);
}

void Point::set(int newx, int newy)
{
    x = newx;
    y = newy;
}


Point Point::operator-(const Point &point) const
{
    return Point(x - point.x, y - point.y ,true);
}

Point Point::operator+(const Point& point) const
{
    return Point(x + point.x, y + point.y, true);
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
    return Point(x >> n, y >> n , true);
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

void Point::drawPoint(QImage *pBackBuffer, int x1, int y1, int scale)
{

    int delta_x = 0;
    int delta_y = 0;

        delta_x = x + pBackBuffer->width() / 2 + x1;
        delta_y = y + pBackBuffer->height() / 2 + y1;

        if (delta_x > 0 &&
            delta_x < pBackBuffer->width() &&
            delta_y > 0 &&
            delta_y < pBackBuffer->height())
        {
            memset(pBackBuffer->bits() + (delta_y * pBackBuffer->bytesPerLine()) + delta_x*3*sizeof(uchar),
                   qRgb(255, 255, 255),
                   sizeof(uchar)*3);
        }
}

void Point::setX(int x)
{
    this->x = x;
}

