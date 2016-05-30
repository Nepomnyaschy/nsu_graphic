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

    lines_2_points.clear();
    lines_3_points.clear();

       if (glyph->outline)
       {

            for(int i = 0; i < glyph->glyphpoints.size(); i++)
            {
                cur = glyph->glyphpoints.at(i);
                cur->drawPoint(pBackBuffer, glyph->x, glyph->y, glyph->scale);

                if(i != glyph->glyphpoints.size() - 1)
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
             p->drawPoint(pBackBuffer, glyph->x, glyph->y, glyph->scale);
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
                   p->drawPoint(pBackBuffer, glyph->x, glyph->y, glyph->scale);
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
                   p->drawPoint(pBackBuffer, glyph->x, glyph->y, glyph->scale);
                   y += dy;
                   d += 2 * lengthX;
                   if (d > 0) {
                         d -= 2 * lengthY;
                         x += dx;
                   }
             }
       }

       delete p;
}

void Font::bezE(Point *from, Point *help, Point *to, QImage *pBackBuffer)
{

        int hyp1 = findlen(from, help);
        int hyp2 = findlen(to, help);
        int steps = 0;

        if(hyp1 >= hyp2)
        {
            steps = hyp1;
        }
        else
        {
            steps = hyp2;
        }



        Point deltastart;
        deltastart.x = from->x - help->x;
        deltastart.y = from->y - help->y;
        Point deltaend;
        deltaend.x = help->x - to->x;
        deltaend.y = help->y - to->y;


        Point curstart;
        curstart.x = steps * from->x;
        curstart.y = steps * from->y;
        Point curend;
        curend.x = steps * help->x;
        curend.y =  steps * help->y;
        Point curdelta;
        Point *prev = new Point();
        Point *cur = new Point();
        int i = 0;
        for (int t = 0; t <= steps; t++)
        {
            curstart = curstart - deltastart;
            curend = curend - deltaend;

            curdelta.x = (curend.x - curstart.x) / steps;
            curdelta.y = (curend.y - curstart.y) / steps;

            cur->x = static_cast<int>(((curstart.x + (t) * (curdelta.x))) / steps);
            cur->y = static_cast<int>(((curstart.y + (t) * (curdelta.y))) / steps);


            if(i > 0)
            {
                line(prev, cur, pBackBuffer);
            }
            prev->x = cur->x;
            prev->y = cur->y;

            i++;
        }
}

void Font::fill(QImage *pBackBuffer)
{
   auto yminmax = std::minmax_element(glyph->glyphpoints.begin(), glyph->glyphpoints.end(),[](Point* a, Point* b) { return a->y > b->y; });

   std::vector<int> intersections;
   Point *online1;
   Point *online2;
   Point *online3;

   for (int y = (*yminmax.first)->y; y > (*yminmax.second)->y; y--) {
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
           }
       }

       foreach (auto line, lines_3_points) {
           online1 = line.at(0);
           online2 = line.at(1);
           online3 = line.at(2);

           int ycenter = 0.25 * online1->y + 0.5 * online2->y + 0.25 * online3->y;
           if (y <= std::max(std::max(online1->y, ycenter), online3->y) && y > std::min(std::min(online1->y, ycenter), online3->y)) {
               intersections.push_back(findBezEPoint(online1, online2, online3, y));
           }
        }

            if (intersections.size() % 2 == 0)
            {
               std::sort(intersections.begin(), intersections.end());
               for (size_t i = 0; i < intersections.size(); i += 2)
                {
                   drawHorizon(pBackBuffer, intersections.at(i), intersections.at(i+1), y);
                }
            }
       }
   }
}

void Font::drawHorizon(QImage *pBackBuffer, int xFrom, int xTo, int y)
{
        xFrom = xFrom + pBackBuffer->width()/2 + glyph->x;
        xTo = xTo + pBackBuffer->width()/2 + glyph->x;

        y = y  + glyph->y + pBackBuffer->height()/2;

        if (y < 0 || y >= pBackBuffer->height()) {
            return;
        }
        if (xFrom < 0) {
            xFrom = 0;
        }
        if (xFrom >= pBackBuffer->width()) {
            xFrom = pBackBuffer->width() - 1;
        }
        if (xTo < 0) {
            xTo = 0;
        }
        if (xTo >= pBackBuffer->width()) {
            xTo = pBackBuffer->width() - 1;
        }
        std::array<uchar , 3> color;

        for (int x = xFrom; x < xTo; x++) {
            memset(pBackBuffer->bits() + (y * pBackBuffer->bytesPerLine()) + x*3*sizeof(uchar),
                   qRgb(255, 255, 255),
                   sizeof(uchar)*3);
        }

    }

int Font::findBezEPoint(Point *p1, Point *p2, Point *p3, int y)
{
    int res;

    int denominator = p1->y - 2 * p2->y + p3->y;
    float discriminant = denominator * y + sqr(p2->y) - p1->y * p3->y;
    float discriminantSqrt = std::sqrt(discriminant);
    float t = (p1->y - p2->y + discriminantSqrt) / denominator;
    if (t < 0 || t > 1) t = t - (2 * discriminantSqrt / denominator);
    return ((1 - t) * (1 - t) * p1->x + 2 * t * (1 - t) * p2->x + t * t * p3->x);

    return res;
}





