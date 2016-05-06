#include "mainwindow.h"
#include <QApplication>
#include "config.h"
#include "canvas.h"


int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        QMap<QString, int> map;
        Config::loadJson(QString(argv[1]), map);
        Lemniscate *lemniscate = new Lemniscate();
        Canvas canvas;
        lemniscate->setX1(map["x1"]);
        lemniscate->setX2(map["x2"]);
        lemniscate->setY1(map["y1"]);
        lemniscate->setY2(map["y2"]);
        canvas.saveImageFromCmd(lemniscate, QString(argv[2]), map["width"], map["height"]);
        return 0;
    }
    QApplication a(argc, argv);
    MainWindow wdgt;
    wdgt.show();

    return a.exec();
}
