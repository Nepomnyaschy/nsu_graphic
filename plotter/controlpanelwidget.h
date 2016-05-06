#ifndef CONTROLPANELWIDGET_H
#define CONTROLPANELWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QSpinBox>
#include <QSlider>

class ControlPanelWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ControlPanelWidget(QWidget *parent = 0);
    ~ControlPanelWidget();
    int getX1() {return X1;}
    int getX2() {return X2;}
    int getY1() {return Y1;}
    int getY2() {return Y2;}

signals:
    void X1Changed(int newx1);
    void X2Changed(int newx2);
    void Y1Changed(int newy1);
    void Y2Changed(int newy2);

public slots:
    void setX1(int x1);
    void setX2(int x2);
    void setY1(int y1);
    void setY2(int y2);

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

   QSlider* slider3;
   QSpinBox* spinbox3;
   QLabel* label3;


   int X1;
   int X2;
   int Y1;
   int Y2;
};

#endif // CONTROLPANELWIDGET_H
