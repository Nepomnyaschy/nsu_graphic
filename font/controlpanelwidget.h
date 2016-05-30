#ifndef CONTROLPANELWIDGET_H
#define CONTROLPANELWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QSpinBox>
#include <QSlider>
#include <QPoint>
#include <QCheckBox>

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
    void FillChanged(bool b);
    void OutlineChanged(bool b);

public slots:
    void setX(int x);
    void setY(int y);
    void setScale(int s);
    void setFill(bool b);
    void setOutline(bool b);
    void shift(QPoint p);

public:
//protected:

//private:

   QSlider* slider;
   QSpinBox* spinbox;
   QLabel* label;

   QSlider* slider1;
   QSpinBox* spinbox1;
   QLabel* label1;

   QSlider* slider2;
   QSpinBox* spinbox2;
   QLabel* label2;

   QCheckBox* checkbox1;
   QCheckBox* checkbox2;


    int X = 0;
    int Y = 0;
    int Scale;
    bool fill;
    bool outline;
};

#endif // CONTROLPANELWIDGET_H
