#include "coordinate.h"

Coordinate::Coordinate()
{
}

void Coordinate::draw(QImage *pBackBuffer)
{
     memset(pBackBuffer->bits() + (pBackBuffer->height()/2 * pBackBuffer->bytesPerLine()),
            qRgb(255,0,0),
            pBackBuffer->width()*sizeof(uchar)*3);

     for (int y = 0; y < pBackBuffer->height(); ++y) {
            memset(pBackBuffer->bits() + (y * pBackBuffer->bytesPerLine()) + (pBackBuffer->width() / 2) * sizeof(uchar)*3,
                   qRgb(255,0,0),
                   sizeof(uchar)*3);
    }
}

