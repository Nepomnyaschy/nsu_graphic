#include "coordinatesystem.h"


CoordinateSystem::CoordinateSystem()
{

}

void CoordinateSystem::draw(QImage *pBackBuffer)
{
    /*
     * draw vertical line
     */
    for (int y = 0; y < pBackBuffer->height(); ++y)
    {
                memset(pBackBuffer->bits()
                       + (y * pBackBuffer->bytesPerLine()) + (pBackBuffer->width() / 2) * sizeof(uchar)*3,
                       qRgb(150,150,150),
                       sizeof(uchar)*3);
    }
    /*
     * draw horizontal line
     */
     memset(pBackBuffer->bits() + (pBackBuffer->height()/2 * pBackBuffer->bytesPerLine()),
            qRgb(150,150,150),
            pBackBuffer->width()*sizeof(uchar)*3);
}

