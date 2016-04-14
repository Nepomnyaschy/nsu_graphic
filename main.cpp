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
        Circle *circle = new Circle();
        Canvas canvas;
        circle->setX(map["x"]);
        circle->setY(map["y"]);
        circle->setR(map["r"]);
        canvas.saveImageFromCmd(circle, QString(argv[2]), map["width"], map["height"]);
        return 0;
    }
    QApplication a(argc, argv);
	MainWindow wdgt;
    wdgt.show();

    return a.exec();
}
