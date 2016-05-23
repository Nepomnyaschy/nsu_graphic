#include "drawwidget.h"
#include <QVBoxLayout>
#include <QGroupBox>
#include <QPainter>
#include <QString>
#include <QDebug>
#include <QFileDialog>
#include <QDir>
#include <math.h>


DrawWidget::DrawWidget(QWidget *parent) :
    QWidget(parent)
{
//    circle = new Circle(this);
//    lemniscate = new Lemniscate(this);

    Glyph *glyph = new Glyph();
    QString fileName = "C:\\dev\\qt\\lab2dot1\\glyph_sample.json";

   /* QString fileName = QFileDialog::getOpenFileName(
        this, tr("Load file"), QDir::currentPath(), tr("All files (*.json)")
    );*/

    glyph->loadFromJson(fileName);


    font = new Font(this);
    font->glyph = glyph;
    axes = new CoordinateSystem();

    auto box = new QGroupBox("DrawWidget");
    auto boxWrapper = new QVBoxLayout();
    box->setStyleSheet("QGroupBox { border: 2px solid gray; border-radius: 4px; }");
    boxWrapper->addWidget(box);
    setLayout(boxWrapper);

}

void DrawWidget::setX1(int x)
{
 //lemniscate->setX1(x);
 QWidget::update();
}


void DrawWidget::setX2(int x)
{
 //lemniscate->setX2(x);
 QWidget::update();
}

void DrawWidget::setY1(int y)
{
 //lemniscate->setY1(y);
 QWidget::update();
}

void DrawWidget::setY2(int y)
{
 //lemniscate->setY2(y);
 QWidget::update();
}

void DrawWidget::paintEvent(QPaintEvent *)
{
    painter = new QPainter(this);
    backBuffer =  new QImage(width(), height(), QImage::Format_RGB888);
    axes->draw(backBuffer);
    //lemniscate->draw(backBuffer);
    font->draw(backBuffer);

    painter->drawImage(0,0, *backBuffer);
}

void DrawWidget::savePicture(QString filename)
{
    painter = new QPainter(this);
    backBuffer =  new QImage(width(), height(), QImage::Format_RGB888);

    axes->draw(backBuffer);
    //lemniscate->draw(backBuffer);

    backBuffer->save(filename, "png");
}


DrawWidget::~DrawWidget()
{

}
