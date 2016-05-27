#include "sphere.h"
#include <QDebug>
#include <cmath>
#include <tgmath.h>
#include <stdio.h>
#include <QImage>
#include <QColor>
#include <QRgb>
#include <algorithm>
#include <functional>

Sphere::Sphere(QObject *parent)
{

}


void Sphere::draw(QImage *pBackBuffer)
{
    if(pBackBuffer == nullptr){
        qDebug() << "wrong buffer";
    }

    text = new QImage("C:\\dev\\nsu_graphic\\sphere\\earth.jpg");



    width = pBackBuffer->width();
    height = pBackBuffer->height();
    bytesperline = pBackBuffer->bytesPerLine();
    uchar *pubBuffer = pBackBuffer->bits();


    int r = r1 * (1 + Scale / (Scale > 0 ? 100 : 1000));

    std::pair<double, double> uv;
    QRgb color;

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            shift_x = (2 * x) - width;
            shift_y = (2 * y) - height;
            if (4 * r * r < sqr(shift_y) + sqr(shift_x)) {
                continue;
            }
            if(bilinear)
            {
                uv = getUV({x, y}, r);
                color = getBillColor(uv);
                std::array<uchar, 3> colors = {qRed(color), qGreen(color), qBlue(color)};
                std::copy(colors.begin(), colors.end(), pubBuffer + 3 * x + bytesperline * y);
            }
            else
            {
                uv = getUV({x, y}, r);
                color = getNearColor(uv);
                std::array<uchar, 3> colors = {qRed(color), qGreen(color), qBlue(color)};
                std::copy(colors.begin(), colors.end(), pubBuffer + 3 * x + bytesperline * y);
            }
        }
    }
}

std::pair<double, double> Sphere::getUV(std::pair<int, int> p, int r)
{
    double x = p.first;
    double y = p.second;
    double z = std::sqrt(4 * r * r - sqr(shift_x) - sqr(shift_y));

    double shifted_x = 2 * x - width;
    double shifted_y = 2 * y - height;

    double u = 1 - (std::atan2(z, shifted_x) / (2 * pi)) ;
    double v = 1 - (std::acos(shifted_y/(2*r)) / pi);
    return {u, v};
}

QRgb Sphere::getNearColor(std::pair<double, double> uv)
{
        int x = std::round(0.5 + uv.first * text->width() + X);
        int y = std::round(0.5 + uv.second * text->height() + Y);
        int x1;
        int y1;
        if(x > 0)
        {
            x1 = 0;
        }
        else
        {
            x1 = text->width() - 1;
        }

        if(y > 0)
        {
            y1 = 0;
        }
        else
        {
            y1 = text->height() - 1;
        }
        x = x % text->width() + x1;
        y = y % text->height() + y1;
        return text->pixel(x, y);
}

QRgb Sphere::getBillColor(std::pair<double, double> uv)
{

        double u = text->width() * uv.first - 0.5;
        double v = text->height() * uv.second - 0.5;

        int x = std::floor(u);
        int y = std::floor(v);

        double u_ratio = u - x;
        double v_ratio = v - y;

        double u_opposite = 1 - u_ratio;
        double v_opposite = 1 - v_ratio;

        std::vector<QColor> cs{ getColor(x, y), getColor(x+1, y), getColor(x, y+1), getColor(x+1, y+1) };

        double red = (cs[0].red() * u_opposite + cs[1].red() * u_ratio) * v_opposite +
                (cs[2].red() * u_opposite + cs[3].red() * u_ratio) * v_ratio;

        double green = (cs[0].green() * u_opposite + cs[1].green() * u_ratio) * v_opposite +
                (cs[2].green() * u_opposite + cs[3].green() * u_ratio) * v_ratio;

        double blue = (cs[0].blue() * u_opposite + cs[1].blue() * u_ratio) * v_opposite +
                (cs[2].blue() * u_opposite + cs[3].blue() * u_ratio) * v_ratio;

        int r = std::round(red);
        int g = std::round(green);
        int b = std::round(blue);




        QColor color(r,g,b);
        return color.rgb();
}


QColor Sphere::getColor(int x, int y){
    int nx = std::fmod(text->width() + x + X, text->width());
    int ny = std::fmod(text->height() + y + Y, text->height());
    return QColor(text->pixel(nx, ny));
}













