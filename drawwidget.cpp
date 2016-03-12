#include "drawwidget.h"
#include <QVBoxLayout>
#include <QGroupBox>
#include <QPainter>
#include <math.h>


DrawWidget::DrawWidget(QWidget *parent) :
    QWidget(parent), xp(0) , yp(0) ,r(50)
{
    auto box = new QGroupBox("DrawWidget");
    auto boxWrapper = new QVBoxLayout();
    box->setStyleSheet("QGroupBox { border: 2px solid gray; border-radius: 4px; }");
    boxWrapper->addWidget(box);
    setLayout(boxWrapper);

    //circle = new Circle(this);



}

void DrawWidget::setX(int x)
{
 xp = -x;
 QWidget::update();
}

void DrawWidget::setY(int y)
{
 yp = -y;
 QWidget::update();
}

void DrawWidget::setR(int radius)
{
 r = radius;
 QWidget::update();
}

void DrawWidget::paintEvent(QPaintEvent *)
{
    painter = new QPainter(this);
    backBuffer =  new QImage(width(), height(), QImage::Format_RGB888);


    uchar* pubBuffer = backBuffer->bits();
    if (!pubBuffer)
    {
        return;
    }


    int x = this->height();
    int y = this->width();

    int x0 = (int)x/2;
    int y0 = (int)y/2;

    int xc;
    int yc;

    for(int i = 0; i <= this->height() - 1; i++)
    {
        for(int j = 0; j <= this->width(); j++)
            {

        yc = y0 - j;
        xc = i - x0;

            if((xp - xc)*(xp - xc) + (yc - yp)*(yc - yp) < r*r)
         {
             memset(pubBuffer + i * backBuffer->bytesPerLine() + (sizeof(uchar) * 3 * j),
                             50,
                             sizeof(uchar) * 3);
         }
         else
         {
             memset(pubBuffer + i * backBuffer->bytesPerLine() + (sizeof(uchar) * 3 * j),
                             200,
                             sizeof(uchar) * 3);
         }

        }
    }

    painter->drawImage(0,0, *backBuffer);
}

DrawWidget::~DrawWidget()
{

}

