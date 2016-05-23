#include "glyphloader.h"

GlyphLoader::GlyphLoader()
{
}

Glyph GlyphLoader::loadFromJson(QString filename, Glyph glyph)
{
    QFile file;
       file.setFileName(path);
       file.open(QIODevice::ReadOnly | QIODevice::Text);
       QJsonDocument document = QJsonDocument::fromJson(file.readAll());
       file.close();
       QJsonObject jsonObject = document.object();

       QJsonObject position = jsonObject["position"].toObject();
       int x = position["x"].toInt();
       int y = position["y"].toInt();

       int scale = jsonObject["scale"].toInt();
       bool fill = jsonObject["fill"].toBool();
       bool outline = jsonObject["outline"].toBool();

       QJsonArray glyphsArray = jsonObject["glyphs"].toArray();
       QJsonArray glyphArray;
       QJsonObject pointObject;
       for (auto glyph : glyphsArray) {
           glyphArray = glyph.toArray();
           std::vector<GlyphPoint * > glyphPoints;
           for (auto point : glyphArray) {
               pointObject = point.toObject();
               position = pointObject["position"].toObject();
               glyphPoints.push_back(new GlyphPoint(position["x"].toInt(), position["y"].toInt(), pointObject["oncurve"].toBool()));
           }
           glyphs.push_back(glyphPoints);
       }
}



