#include "lemniscate.h"
#include <cmath>
#include <QString>
#include <limits.h>
#include "QDebug"
Lemniscate::Lemniscate(QObject *parent) : QObject(parent), DEBUG(false), focus1(-50,50), focus2(50,50){}


void Lemniscate::setX1(int x1)
{
    focus1.setX(x1);
}

void Lemniscate::setX2(int x2)
{
    focus2.setX(x2);
}

void Lemniscate::setY1(int y1)
{
    focus1.setY(y1);
}

void Lemniscate::setY2(int y2)
{
    focus2.setY(y2);
}


/*
 * draw lemniscate
 */
void Lemniscate::draw(QImage *pBackBuffer)
{
    distanceBetweenFocuses = (focus1 - focus2).square() * (focus1 - focus2).square();
    if(DEBUG) qDebug() << "distance:" << distanceBetweenFocuses << " " <<  focus1.getX() << " " << focus1.getY() << " " << focus2.getX() << " " <<  focus2.getY();


    /*
     * binary search for first point
     * to start draw lemniscate
     * returns 2 points
     */

    Point tmp = focus2 - focus1;
    Point left = focus1 - tmp;
    Point right = focus1;
    Point center;

//    if(DEBUG) qDebug() << "distance to focuses" << (center);

    while((left - right).square() > 2)
    {
        center = (left + right) >> 1;
         if(DEBUG) qDebug() << "center x and y for first" <<  center.getX(), center.getY();
         if(distanceToFocuses(center) > distanceBetweenFocuses)
         {
             left = center;
         }
         else
         {
             right = center;
         }
    }

    if(DEBUG)qDebug() << "firsts points x" << center.getX() << " " << (focus1 + focus2 - center).getX();

    // creating 4 points to start draw
    // each part of lemniscate
    drawPart(center,     Point(-(center-focus1).y, ((center-focus1).x)), pBackBuffer);
    drawPart(center,     Point((center-focus1).y, -((center-focus1).x)), pBackBuffer);
    drawPart(focus1 + focus2 - center,    Point((focus1 - center).y, -((focus1 - center).x)), pBackBuffer);
    drawPart(focus1 + focus2 - center,    Point(-(focus1 - center).y, ((focus1 - center).x)), pBackBuffer);

}

/*
 * draw one part of lemniscate
 */
void Lemniscate::drawPart(Point point, Point direction, QImage *pBackBuffer)
{
    int i = 0;

    Point center_point = (focus1 + focus2) >> 1;
    qDebug() << "after X = " << center_point.getX() << "Y = " << center_point.getY();

    while ((point - center_point).square() >= 1)
    {
        i++;
        if(i > 1000) break;

        std::pair<Point,Point> pair = findNextPoint(point, direction);
        point = pair.first;
        direction = pair.second;
        drawPoint(point, pBackBuffer);
    }
}

/*
 * stepping for all dirs to
 * find a correct direction
 */
std::pair<Point, Point> Lemniscate::findNextPoint(Point& point, Point& direction)
{
    minDistance = LLONG_MAX;
    Point nextDir;
    for(auto& dir : directions)
    {
        if (direction * dir > 0)
        {
            Point p = dir+point;
            long long dist = distanceToFocuses(p);
            long long absDist = llabs(dist - distanceBetweenFocuses);
            if (absDist < minDistance)
            {
                minDistance = absDist;
                nextDir = dir;
            }
        }
    }
    return { nextDir + point, nextDir };
}


long long Lemniscate::distanceToFocuses(Point& p)
{
    return 16 * (p-focus1).square() * (p-focus2).square();
}

/*
 * draw a single point
 */
void Lemniscate::drawPoint(Point p, QImage *pBackBuffer)
{
    int delta_x = p.getX() + pBackBuffer->width() / 2;
    int delta_y = p.getY() + pBackBuffer->height() / 2;

    if (delta_x > 0 &&
        delta_x < pBackBuffer->width() &&
        delta_y > 0 &&
        delta_y < pBackBuffer->height())
    {
        memset(pBackBuffer->bits() + (delta_y * pBackBuffer->bytesPerLine()) + delta_x*3*sizeof(uchar),
               qRgb(255, 255, 255),
               sizeof(uchar)*3);
    }
}
