#ifndef CIRCLE_H
#define CIRCLE_H

#include <QImage>
#include <QObject>
#include <QPainter>

#include <QWidget>
#include "circle.h"

class Circle : public QWidget
{
    Q_OBJECT
public:
    explicit Circle(QWidget *parent = 0);
    ~Circle();


    int x;
    int y;
    int r;

signals:

public slots:
    void setX(int);
    void setY(int);
    void setR(int);
protected:

void paintEvent(QPaintEvent *event);

private:


QPainter *painter;
QImage *backBuffer;


};

#endif // CIRCLE_H
