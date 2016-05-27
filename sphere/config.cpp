#include "config.h"

namespace Config
{
    QJsonDocument* saveJson(int x1, int x2, int y1, int y2, int height, int width)
    {
        QJsonObject focus1;
        focus1["x"] = x1;
        focus1["y"] = y1;

        QJsonObject focus2;
        focus2["x"] = x2;
        focus2["y"] = y2;

        QJsonObject lemniscate;
        lemniscate["focus1"] = focus1;
        lemniscate["focus2"] = focus2;

        QJsonObject panel;
        QJsonObject size;
        size["width"] = width;
        size["height"] = height;
        panel["size"] = size;

        QJsonObject outer;
        outer["lemniscate"] = lemniscate;
        outer["panel"] = panel;

        return new QJsonDocument(outer);

    }

    void loadJson(QString fileName, QMap<QString, int>& map) {

        QFile saveFile(fileName);
        if (!saveFile.exists())
        {
            printf("File doesn't exists");
            return;
        }
        saveFile.open(QFile::ReadOnly | QFile::Text);
        QByteArray saveData = saveFile.readAll();
        QJsonDocument jsonSave(QJsonDocument::fromJson(saveData));

        QJsonObject saveObject = jsonSave.object();

        map["width"] = saveObject["panel"].toObject()["size"].toObject()["width"].toInt();
        map["height"] = saveObject["panel"].toObject()["size"].toObject()["height"].toInt();
        map["x1"] = saveObject["lemniscate"].toObject()["focus1"].toObject()["x"].toInt();
        map["y1"] = saveObject["lemniscate"].toObject()["focus1"].toObject()["y"].toInt();
        map["x2"] = saveObject["lemniscate"].toObject()["focus2"].toObject()["x"].toInt();
        map["y2"] = saveObject["lemniscate"].toObject()["focus2"].toObject()["y"].toInt();
    }
}
