#include "drawwidget.h"
#include <QVBoxLayout>
#include <QGroupBox>
#include <QPainter>
#include <QString>
#include <QDebug>
#include <QFileDialog>
#include <QDir>
#include <QApplication>
#include <QMouseEvent>
#include <math.h>


DrawWidget::DrawWidget(QWidget *parent) :
    QWidget(parent)
{
//    circle = new Circle(this);
//    lemniscate = new Lemniscate(this);

    Glyph *glyph = new Glyph();

    QString fileName = "C:\\dev\\qt\\lab2dot1\\glyph_sample.json";

    glyph->loadFromJson(fileName);


    font = new Font(this);
    font->glyph = glyph;
    axes = new CoordinateSystem();

   // auto box = new QGroupBox("DrawWidget");
    //auto boxWrapper = new QVBoxLayout();
    //box->setStyleSheet("QGroupBox { border: 2px solid gray; border-radius: 4px; }");
    //boxWrapper->addWidget(box);
    //setLayout(boxWrapper);


}

void DrawWidget::setX(int x)
{
 font->glyph->x = x;
 QWidget::update();
}


void DrawWidget::setY(int y)
{

 font->glyph->y = y;
 QWidget::update();
}

void DrawWidget::setScale(int scale)
{
 //scale = scale > 0 ? 1 + scale / 100.0 : 1 + scale / 1000.0;
 font->glyph->scale = scale > 0 ? 1 + scale / 100.0 : 1 + scale / 1000.0;
 foreach (auto p, font->glyph->glyphpoints) {
     p->recalc(font->glyph->scale);
 }
    QWidget::update();
}

void DrawWidget::setFill(bool b)
{
    font->glyph->fill = b;
     QWidget::update();
}

void DrawWidget::setOutline(bool b)
{
    font->glyph->outline = b;
     QWidget::update();
}


void DrawWidget::paintEvent(QPaintEvent *)
{
    painter = new QPainter(this);
    backBuffer =  new QImage(width(), height(), QImage::Format_RGB888);
    axes->draw(backBuffer);
    font->draw(backBuffer);
    painter->drawImage(0,0, *backBuffer);
}

void DrawWidget::savePicture(QString filename)
{
    painter = new QPainter(this);
    backBuffer =  new QImage(width(), height(), QImage::Format_RGB888);

    axes->draw(backBuffer);
    font->draw(backBuffer);
    backBuffer->save(filename, "png");
}

void DrawWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
       startPosition = event->pos();   
     }
}

void DrawWidget::mouseMoveEvent(QMouseEvent * event) {
    if (!(event->buttons() & Qt::LeftButton))
    {
            return;
    }
    if ((event->pos() - startPosition).manhattanLength() < QApplication::startDragDistance())
    {
            return;
    }
    QPoint shift = event->pos() - startPosition;
    startPosition = event->pos();
    emit glyphShifted(shift);
}


DrawWidget::~DrawWidget()
{
}
