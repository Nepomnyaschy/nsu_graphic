#include "drawwidget.h"
#include <QVBoxLayout>
#include <QGroupBox>
#include <QPainter>
#include <QString>
#include <math.h>


DrawWidget::DrawWidget(QWidget *parent) :
    QWidget(parent)
{
    circle = new Circle(this);

    auto box = new QGroupBox("DrawWidget");
    auto boxWrapper = new QVBoxLayout();
    box->setStyleSheet("QGroupBox { border: 2px solid gray; border-radius: 4px; }");
    boxWrapper->addWidget(box);
    setLayout(boxWrapper);

}

void DrawWidget::setX(int x)
{
 circle->setX(-x);
 QWidget::update();
}

void DrawWidget::setY(int y)
{
 circle->setY(-y);
 QWidget::update();
}

void DrawWidget::setR(int radius)
{
 circle->setR(radius);
 QWidget::update();
}

void DrawWidget::paintEvent(QPaintEvent *)
{
    painter = new QPainter(this);
    backBuffer =  new QImage(width(), height(), QImage::Format_RGB888);
//    circle->drawByPixels(backBuffer);
    circle->drawByLine(backBuffer);
    painter->drawImage(0,0, *backBuffer);
}

void DrawWidget::savePicture(QString filename)
{
    painter = new QPainter(this);
    backBuffer =  new QImage(width(), height(), QImage::Format_RGB888);
    circle->drawByPixels(backBuffer);
    backBuffer->save(filename, "png");
}


DrawWidget::~DrawWidget()
{

}
