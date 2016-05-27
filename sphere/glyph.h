#ifndef GLYPH_H
#define GLYPH_H


#include <QString>
#include "point.h"

class Glyph
{
public:
    Glyph();

    int scale;
    int x;
    int y;
    bool fill;
    bool outline;
    std::vector<Point *> glyphpoints;


    void loadFromJson(QString filename);

};

#endif // GLYPH_H
