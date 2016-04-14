#include "config.h"

namespace Config
{
    QJsonDocument* saveJson(int x, int y, int r, int height, int width)
    {
        QJsonObject jsonObject;
        QJsonArray jsonCircles;
        QJsonObject jsonPosition;
        QJsonObject jsonPanel;
        QJsonObject jsonSize;
        QJsonObject jsonCircle;

        jsonPosition["x"] = x;
        jsonPosition["y"] = y;
        jsonCircle["r"] = r;
        jsonCircle["position"] = jsonPosition;
        jsonCircles.append(jsonCircle);
        jsonSize["x"] = width;
        jsonSize["y"] = height;
        jsonPanel["size"] = jsonSize;
        jsonObject["circles"] = jsonCircles;
        jsonObject["panel"] = jsonPanel;

        return new QJsonDocument(jsonObject);

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

        map["width"] = saveObject["panel"].toObject()["size"].toObject()["x"].toInt();
        map["height"] = saveObject["panel"].toObject()["size"].toObject()["y"].toInt();
        map["x"] = saveObject["circles"].toArray()[0].toObject()["position"].toObject()["x"].toInt();
        map["y"] = saveObject["circles"].toArray()[0].toObject()["position"].toObject()["y"].toInt();
        map["r"] = saveObject["circles"].toArray()[0].toObject()["r"].toInt();
    }
}
