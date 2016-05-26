#ifndef CONTROLPANELWIDGET_H
#define CONTROLPANELWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QSpinBox>
#include <QSlider>
#include <QPoint>

class ControlPanelWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ControlPanelWidget(QWidget *parent = 0);
    ~ControlPanelWidget();
    int getX() {return X;}
    int getY() {return Y;}
    int getScale() {return Scale;}

signals:
    void XChanged(int newx);
    void YChanged(int newx);
    void ScaleChanged(int newx);

public slots:
    void setX(int x);
    void setY(int y);
    void setScale(int s);
    void shift(QPoint p);


protected:

private:

   QSlider* slider;
   QSpinBox* spinbox;
   QLabel* label;

   QSlider* slider1;
   QSpinBox* spinbox1;
   QLabel* label1;

   QSlider* slider2;
   QSpinBox* spinbox2;
   QLabel* label2;


    int X;
    int Y;
    int Scale;
};

#endif // CONTROLPANELWIDGET_H
