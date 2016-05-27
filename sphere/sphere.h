#ifndef SPHERE_H
#define SPHERE_H


#include <QObject>
#include <QImage>
#include <QColor>
#include <QRgb>

class Sphere : public QObject
{
  Q_OBJECT
public:
  explicit Sphere(QObject *parent = 0);
  void draw(QImage* pBackBuffer);
  std::pair<double, double> getUV(std::pair<int, int> p, int r);
  QRgb getNearColor(std::pair<double, double> uv);
  QRgb getBillColor(std::pair<double, double> uv);
  int sqr(int a){return a*a;}
  QColor getColor(int x, int y);


  int r1 = 256;
  int r = 256;
  int height;
  int width;
  int bytesperline;

  int X = 0;
  int Y = 0;
  int Scale = 0;

  int shift_x;
  int shift_y;


  bool bilinear = true;


  QImage *text;

  double pi = 3.1415926;
private:

};

#endif // SPHERE_H
