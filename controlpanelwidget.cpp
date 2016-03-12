#include "controlpanelwidget.h"
#include <QVBoxLayout>
#include <QGroupBox>


ControlPanelWidget::ControlPanelWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setMinimumWidth(100);
    this->setMinimumHeight(400);

    slider = new QSlider(Qt::Horizontal);
    slider->setMaximum(1000);
    slider->setMinimum(-1000);
    spinbox = new QSpinBox();
    spinbox->setMaximum(1000);
    spinbox->setMinimum(-1000);
    label = new QLabel();

    slider1 = new QSlider(Qt::Horizontal);
    slider1->setMinimum(-1000);
    slider1->setMaximum(1000);
    spinbox1 = new QSpinBox();
    spinbox1->setMaximum(1000);
    spinbox1->setMinimum(-1000);
    label1 = new QLabel();

    slider2 = new QSlider(Qt::Horizontal);
    slider2->setMinimum(-1000);
    slider2->setMaximum(1000);
    spinbox2 = new QSpinBox();
    spinbox2->setMaximum(1000);
    spinbox2->setMinimum(-1000);
    label2 = new QLabel();

    auto box = new QGroupBox("Controls");
    auto boxWrapper = new QVBoxLayout();
    box->setStyleSheet("QGroupBox { border: 2px solid gray; border-radius: 4px; }");

    auto layout = new QGridLayout();
    layout->addWidget(slider, 0, 0);
    layout->addWidget(spinbox, 1, 0);
    layout->addWidget(label, 2, 0);
    layout->addWidget(slider1, 3, 0);
    layout->addWidget(spinbox1, 4, 0);
    layout->addWidget(label1, 5, 0);
    layout->addWidget(slider2, 6, 0);
    layout->addWidget(spinbox2, 7, 0);
    layout->addWidget(label2, 8, 0);

    box->setLayout(layout);
    boxWrapper->addWidget(box);
    setLayout(boxWrapper);

    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));

    connect(slider, &QSlider::valueChanged, spinbox, &QSpinBox::setValue);
    connect(slider, &QSlider::valueChanged, this , &ControlPanelWidget::setR);

    connect(slider1, &QSlider::valueChanged, spinbox1, &QSpinBox::setValue);
    connect(slider1, &QSlider::valueChanged, this , &ControlPanelWidget::setX);

    connect(slider2, &QSlider::valueChanged, spinbox2, &QSpinBox::setValue);
    connect(slider2, &QSlider::valueChanged, this , &ControlPanelWidget::setY);
}

void ControlPanelWidget::setR(int r)
{
        R = r;
        emit RChanged(r);
}

void ControlPanelWidget::setX(int x)
{
        X = x;
        emit XChanged(x);
}

void ControlPanelWidget::setY(int y)
{
        Y = y;
        emit YChanged(y);
}

ControlPanelWidget::~ControlPanelWidget()
{

}
