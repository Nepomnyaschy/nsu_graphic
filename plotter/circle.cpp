#include "circle.h"
#include <QImage>
#include <QDebug>
#include <cmath>

Circle::Circle(QObject *parent) : QObject(parent), x_center(0), y_center(0), r(50) {}

void Circle::drawByPixels(QImage* pBackBuffer){
    uchar* pubBuffer = pBackBuffer->bits();
    if (!pubBuffer)
    {
        return;
    }


    int x = pBackBuffer->height();
    int y = pBackBuffer->width();

    int x0 = (int)x/2;
    int y0 = (int)y/2;

    int xc;
    int yc;

    for(int i = 0; i <= x - 1; i++)
    {
        for(int j = 0; j <= y; j++)
        {

        yc = y0 - j;
        xc = i - x0;

         if((x_center - xc)*(x_center - xc) + (yc - y_center)*(yc - y_center) < r*r)
         {
             memset(pubBuffer + i * pBackBuffer->bytesPerLine() + (sizeof(uchar) * 3 * j),
                             50,
                             sizeof(uchar) * 3);
         }
         else
         {
             memset(pubBuffer + i * pBackBuffer->bytesPerLine() + (sizeof(uchar) * 3 * j),
                             200,
                             sizeof(uchar) * 3);
         }

        }
    }
}

void Circle::drawByLine(QImage *pBackBuffer)
{
    uchar* pubBuffer = pBackBuffer->bits();
    if (!pubBuffer)
    {
        return;
    }

    int dx = x_center + pBackBuffer->width() / 2;
    int dy = y_center + pBackBuffer->height() / 2;
    int from;
    int to;

    for (int y = std::max(0, -r + dy); y < std::min(pBackBuffer->height(), dy + r); y++) {
        int width = getWidth(y, r , dy);



        if(dx - width < 0)
        {
            from = 0;
        }
        else
        {
            from  = std::min(pBackBuffer->width(), dx-width);
        }

        if(dx + width > pBackBuffer->width())
        {
            to = pBackBuffer->width();
        }
        else
        {
            to = std::max(0 , dx + width + 1);
        }
         memset(pubBuffer +
                (y * pBackBuffer->bytesPerLine()) + from*3*sizeof(uchar),
                qRgb(160,160,160),
                (to - from)*sizeof(uchar)*3);
    }
}

int Circle::getWidth(int y, int r, int dy)
{
     return std::sqrt(r*r - (dy-y)*(dy-y));
}

void Circle::setX(int x) {
    this->x_center = x;
}

void Circle::setY(int y) {
    this->y_center = y;
}

void Circle::setR(int r) {
    this->r = r;
}
