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
    int getR() {return R;}
    int getX() {return X;}
    int getY() {return Y;}

signals:
    void RChanged(int newr);
    void XChanged(int newx);
    void YChanged(int newy);

public slots:
    void setR(int r);
    void setX(int x);
    void setY(int y);

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


   int R;
   int X;
   int Y;
};

#endif // CONTROLPANELWIDGET_H
