#include "canvas.h"
#include <QImage>


Canvas::Canvas()
{

}

void Canvas::saveImageFromCmd(Circle *circle, QString filename, int width, int height)
{
    QImage *backBuffer =  new QImage(width, height, QImage::Format_RGB888);
    circle->drawByPixels(backBuffer);
    backBuffer->save(filename, "png");
    printf("done");
}



