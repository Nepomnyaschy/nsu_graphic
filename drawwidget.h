#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QWidget>
#include "circle.h"

class DrawWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DrawWidget(QWidget *parent = 0);
    ~DrawWidget();


    int xp;
    int yp;
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
Circle *circle;


};
#endif // DRAWWIDGET_H
