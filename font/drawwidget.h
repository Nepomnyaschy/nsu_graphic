#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QWidget>
#include "coordinatesystem.h"
#include "glyph.h"
#include "font.h"

class DrawWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DrawWidget(QWidget *parent = 0);
    ~DrawWidget();

signals:

public slots:
    void savePicture(QString filename);
    void setX1(int);
    void setX2(int);
    void setY1(int);
    void setY2(int);
protected:

void paintEvent(QPaintEvent *event);

private:


QPainter *painter;
QImage *backBuffer;
Font *font;
CoordinateSystem *axes;


};
#endif // DRAWWIDGET_H
