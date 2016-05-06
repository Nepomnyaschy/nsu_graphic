#ifndef LEMNISCATE_H
#define LEMNISCATE_H


#include <QObject>
#include <QImage>
#include "point.h"

class Lemniscate : public QObject
{
  Q_OBJECT
public:
  explicit Lemniscate(QObject *parent = 0);
  void setX1(int);
  void setX2(int);
  void setY1(int);
  void setY2(int);
  void draw(QImage* pBackBuffer);


signals:

public slots:
private:
  Point focus1;
  Point focus2;

  long long  distanceBetweenFocuses;
  long long minDistance;

  long long distanceToFocuses(Point& p);
  void drawPart(Point point, Point direction, QImage *pBackBuffer);
  std::pair<Point, Point> findNextPoint(Point& point,Point& direction);

  void drawPoint(Point p, QImage *pBackBuffer);


  /*
   * all possible directions
   * to check where we need to draw lemniscate
   */
  const std::vector<Point> directions =
  {
          Point(0, 1),
          Point(1, 1),
          Point(1, 0),
          Point(1, -1),
          Point(0, -1),
          Point(-1, -1),
          Point(-1, 0),
          Point(-1, 1)
      };


  bool DEBUG;
};

#endif // LEMNISCATE_H
