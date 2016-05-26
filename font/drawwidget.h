#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QWidget>
#include "coordinatesystem.h"
#include "glyph.h"
#include "font.h"
#include <QMouseEvent>

class DrawWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DrawWidget(QWidget *parent = 0);
    ~DrawWidget();

signals:
 void glyphShifted(QPoint shift);

public slots:
    void savePicture(QString filename);
    void setX(int);
    void setY(int);
    void setScale(int);
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent * event);

private:


QPoint startPosition;
QPainter *painter;
QImage *backBuffer;
Font *font;
CoordinateSystem *axes;


};
#endif // DRAWWIDGET_H
