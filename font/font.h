#ifndef FONT_H
#define FONT_H


#include <QObject>
#include <QImage>
#include "point.h"
#include "glyph.h"

class Font : public QObject
{
  Q_OBJECT
public:
  explicit Font(QObject *parent = 0);
  void draw(QImage* pBackBuffer);
  void line(Point* from, Point* to, QImage *pBackBuffer);
  void bezE(Point* from, Point* help, Point* to, QImage *pBackBuffer);
  void fill(QImage *pBackBuffer);
  void drawHorizon(QImage *pBackBuffer, int from, int to, int y);
  int findBezEPoint(Point *p1, Point *p2, Point *p3, int y);

  std::vector<std::vector<Point *>> lines_2_points;
  std::vector<std::vector<Point *>> lines_3_points;
  std::vector<int> intersections;


  Glyph *glyph;

private:

};

#endif // FONT_H
