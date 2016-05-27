#ifndef GLYPHLOADER_H
#define GLYPHLOADER_H

#include "glyph.h"

class GlyphLoader
{
public:
    GlyphLoader();
    Glyph loadFromJson(QString filename);

    std::vector<Glyph> glyphs;
};

#endif // GLYPHLOADER_H
