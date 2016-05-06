#ifndef CANVAS_H
#define CANVAS_H
#include "circle.h"
#include "lemniscate.h"
#include <QString>

class Canvas
{
public:
    Canvas();
    void saveImageFromCmd(Lemniscate *lemniscate, QString filename, int width, int height);
};

#endif // CANVAS_H
