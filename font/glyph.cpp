#include "glyph.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>

Glyph::Glyph()
{

}



void Glyph::loadFromJson(QString filename)
{
       QFile file;
       file.setFileName(filename);
       file.open(QIODevice::ReadOnly | QIODevice::Text);
       QJsonDocument document = QJsonDocument::fromJson(file.readAll());
       file.close();
       QJsonObject jsonObject = document.object();

       QJsonObject position = jsonObject["position"].toObject();
       x = position["x"].toInt();
       y = position["y"].toInt();

       scale = jsonObject["scale"].toInt();
       scale = scale > 0 ? 1 + scale / 100.0 : 1 + scale / 1000.0;
       fill = jsonObject["fill"].toBool();
       outline = jsonObject["outline"].toBool();

       QJsonArray glyphsArray = jsonObject["glyphs"].toArray();
       QJsonArray glyphArray;
       QJsonObject pointObject;
       for (auto glyph : glyphsArray) {
           glyphArray = glyph.toArray();

           for (auto point : glyphArray) {
               pointObject = point.toObject();
               position = pointObject["position"].toObject();

               Point *p = new Point();
               p->x = position["x"].toInt();
               p->xorig = position["x"].toInt();
               p->y = position["y"].toInt();
               p->yorig = position["y"].toInt();
               p->oncurve = pointObject["oncurve"].toBool();

               glyphpoints.push_back(p);
           }
       }


       qDebug() << "JSON_LOADER_DONE" ;
       qDebug() << glyphpoints.size();

}
