#include "canvas.h"
#include <QImage>


Canvas::Canvas()
{

}

void Canvas::saveImageFromCmd(Lemniscate *lemniscate, QString filename, int width, int height)
{
    QImage *backBuffer =  new QImage(width, height, QImage::Format_RGB888);
    lemniscate->draw(backBuffer);
    backBuffer->save(filename, "png");
    printf("done");
}



