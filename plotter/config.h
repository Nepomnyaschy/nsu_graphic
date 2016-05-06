#ifndef CONFIG_H
#define CONFIG_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QByteArray>
#include <QFile>
#include <QMap>

namespace Config
{
    QJsonDocument* saveJson(int x1, int x2, int y1, int y2, int height, int width);
    void loadJson(QString fileName, QMap<QString, int>& map);
}

#endif // CONFIG_H
