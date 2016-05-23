#include "font.h"
#include <QDebug>


Font::Font(QObject *parent) : QObject(parent){}

void Font::draw(QImage *pBackBuffer)
{
    if(pBackBuffer == nullptr){
        qDebug() << "wrong buffer";
    }

    Point * prev;
    Point * next;
    Point * cur;


       if (glyph->outline)
       {

            for(int i = 0; i < glyph->glyphpoints.size(); i++)
            {
                cur = glyph->glyphpoints.at(i);
                cur->drawPoint(pBackBuffer);

                if(i !=  glyph->glyphpoints.size() - 1)
                {
                    next = glyph->glyphpoints.at(i + 1);
                }
                else
                {
                    next = glyph->glyphpoints.at(0);
                }

                if(next->oncurve && cur->oncurve)
                {
                    line(cur, next, pBackBuffer);
                    lines_2_points.push_back(std::vector<Point *>{cur, next});
                }
                else if(!cur->oncurve)
                {
                    if(i != 0)
                    {
                        prev = glyph->glyphpoints.at(i - 1);
                    }
                    else
                    {
                        prev = glyph->glyphpoints.at(glyph->glyphpoints.size());
                    }
                    bezE(prev, cur, next, pBackBuffer);
                    lines_3_points.push_back(std::vector<Point *>{prev, cur, next});
                }
            }
       }

       if(glyph->fill)
       fill(pBackBuffer);
}

void Font::line(Point* from, Point* to, QImage *pBackBuffer)
{
       Point *p = new Point();

       int x1 = from->getX();
       int x2 = to->getX();

       int y1 = from->getY();
       int y2 = to->getY();

       int dx = (x2 - x1 >= 0 ? 1 : -1);
       int dy = (y2 - y1 >= 0 ? 1 : -1);

       int lengthX = std::abs(x2 - x1);
       int lengthY = std::abs(y2 - y1);

       int length = std::max(lengthX, lengthY);

       if (length == 0)
       {
             p->x = x1; p->y = y1;
             p->drawPoint(pBackBuffer);
       }

       if (lengthY <= lengthX)
       {
             int x = x1;
             int y = y1;
             int d = -lengthX;

             length++;
             while(length--)
             {
                   p->x = x; p->y = y;
                   p->drawPoint(pBackBuffer);
                   x += dx;
                   d += 2 * lengthY;
                   if (d > 0) {
                         d -= 2 * lengthX;
                         y += dy;
                   }
             }
       }
       else
       {
             int x = x1;
             int y = y1;
             int d = - lengthY;

             length++;
             while(length--)
             {
                   p->x = x; p->y = y;
                   p->drawPoint(pBackBuffer);
                   y += dy;
                   d += 2 * lengthX;
                   if (d > 0) {
                         d -= 2 * lengthY;
                         x += dx;
                   }
             }
       }
}

void Font::bezE(Point *from, Point *help, Point *to, QImage *pBackBuffer)
{

       int coef = 500;


        Point deltastart;
        deltastart.x = from->x - help->x;
        deltastart.y = from->y - help->y;
        Point deltaend;
        deltaend.x = help->x - to->x;
        deltaend.y = help->y - to->y;


        Point curstart;
        curstart.x = coef * from->x;
        curstart.y = coef * from->y;
        Point curend;
        curend.x = coef * help->x;
        curend.y =  coef * help->y;
        Point curdelta;
        Point *cur = new Point();
        for (int t =0; t <= coef; t++) {
            curstart = curstart - deltastart;
            curend = curend - deltaend;

            curdelta.x = (curend.x - curstart.x) / coef;
            curdelta.y = (curend.y - curstart.y) / coef;

            cur->x = (curstart.x + t * curdelta.x) / coef;
            cur->y = (curstart.y + t * curdelta.y) / coef;

            cur->drawPoint(pBackBuffer);
        }
}

void Font::fill(QImage *pBackBuffer)
{
   Point *online1;
   Point *online2;
   Point *online3;
   for(int y = 1 ; y < (pBackBuffer->byteCount()/pBackBuffer->bytesPerLine()) - 2 ; y++)
   {
       intersections.clear();
       foreach (auto line, lines_2_points) {
           online1 = line.at(0);
           online2 = line.at(1);
           if ((online1->y >= y && online2->y < y) ||
               (online1->y < y && online2->y >= y))
           {
                int x = online1->x + ((y - online1->y) * (online2->x - online1->x)) / (online2->y - online1->y);
                intersections.push_back(x);
                //qDebug() << x;
           }
       }

       foreach (auto line, lines_3_points) {
           online1 = line.at(0);
           online2 = line.at(1);
           online2 = line.at(2);

           int center = 0.25 * online1->y + 0.5 * online2->y + 0.25 * online3->y;
           if(y <= std::max(std::max(online1->y, center), online3->y) && y > std::min(std::min(online1->y, center), online3->y))
           {
               intersections.push_back(findBezEPoint(online1, online2, online3, y));
           }
       }


       std::sort(intersections.begin(), intersections.end());
       if (intersections.size() % 2 == 0) {
           for (int i = 0; i < intersections.size(); i += 2) {
               drawHorizon(pBackBuffer, intersections.at(i), intersections.at(i + 1), y);
           }
       }
   }
}

void Font::drawHorizon(QImage *pBackBuffer, int from, int to, int y)
{
    from = from + pBackBuffer->width() / 2;
    to = to + pBackBuffer->width() / 2;
    y = y + pBackBuffer->height() / 2;

    if (y < 0 || y >= pBackBuffer->height()) {
           return;
       }
       if (from < 0) {
           from = 0;
       }
       if (from >= pBackBuffer->width()) {
           from = pBackBuffer->width() - 1;
       }
       if (to < 0) {
           to = 0;
       }
       if (to >= pBackBuffer->width()) {
           to = pBackBuffer->width() - 1;
       }

         memset(pBackBuffer->bits() +
                (y * pBackBuffer->bytesPerLine()) + from*3*sizeof(uchar),
                qRgb(160,160,160),
                (to - from)*sizeof(uchar)*3);
}

int Font::findBezEPoint(Point *p1, Point *p2, Point *p3, int y)
{
    int a = p1->y;
    int b = p2->y;
    int c = p3->y;
    int d = y;

    float t1 = ((a - b) + std::sqrt(- a * c + a * d + b*b + c*d - 2 * b * d)) / a - 2 * b + c;
    float t2 = ((a - b) - std::sqrt(- a * c + a * d + b*b + c*d - 2 * b * d)) / a - 2 * b + c;

    //return (1 - t1) * (1 - t1) * p1->x + 2 * t1 * (1 - t1) * p2->x + t1 * t1 * p3->x;
    return (1 - t2) * (1 - t2) * p1->x + 2 * t2 * (1 - t2) * p2->x + t2 * t2 * p3->x;
}



