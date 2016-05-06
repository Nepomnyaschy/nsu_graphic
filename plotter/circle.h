#ifndef CIRCLE_H
#define CIRCLE_H

#include <QObject>
#include <QImage>

class Circle : public QObject
{
  Q_OBJECT
public:
  explicit Circle(QObject *parent = 0);
  void setX(int x);
  void setY(int y);
  void setR(int r);
  void drawByPixels(QImage* pBackBuffer);
  void drawByLine(QImage * pBackBuffer);
  void drawLine(int , int , int);
  int getWidth(int y, int r, int dy);
signals:

public slots:
private:
  int x_center;
  int y_center;
  int r;
};

#endif // CIRCLE_H
