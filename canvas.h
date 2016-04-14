#ifndef CANVAS_H
#define CANVAS_H
#include "circle.h"
#include <QString>

class Canvas
{
public:
    Canvas();
    void saveImageFromCmd(Circle *circle, QString filename, int width, int height);
};

#endif // CANVAS_H
