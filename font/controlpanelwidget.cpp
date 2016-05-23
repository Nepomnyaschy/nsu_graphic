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

    slider3 = new QSlider(Qt::Horizontal);
    slider3->setMinimum(-1000);
    slider3->setMaximum(1000);
    spinbox3 = new QSpinBox();
    spinbox3->setMaximum(1000);
    spinbox3->setMinimum(-1000);
    label3 = new QLabel();

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
    layout->addWidget(slider3, 9, 0);
    layout->addWidget(spinbox3, 10, 0);
    layout->addWidget(label3, 11, 0);

    box->setLayout(layout);
    boxWrapper->addWidget(box);
    setLayout(boxWrapper);

    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));

    connect(slider, &QSlider::valueChanged, spinbox, &QSpinBox::setValue);
    connect(slider, &QSlider::valueChanged, this , &ControlPanelWidget::setX1);
    connect(spinbox, SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));
    connect(spinbox, SIGNAL(valueChanged(int)), this, SLOT(setValue(int)));

    connect(slider1, &QSlider::valueChanged, spinbox1, &QSpinBox::setValue);
    connect(slider1, &QSlider::valueChanged, this , &ControlPanelWidget::setX2);
    connect(spinbox1, SIGNAL(valueChanged(int)), slider1, SLOT(setValue(int)));
    connect(spinbox1, SIGNAL(valueChanged(int)), this, SLOT(setValue(int)));

    connect(slider2, &QSlider::valueChanged, spinbox2, &QSpinBox::setValue);
    connect(slider2, &QSlider::valueChanged, this , &ControlPanelWidget::setY1);
    connect(spinbox2, SIGNAL(valueChanged(int)), slider2, SLOT(setValue(int)));
    connect(spinbox2, SIGNAL(valueChanged(int)), this, SLOT(setValue(int)));


    connect(slider3, &QSlider::valueChanged, spinbox3, &QSpinBox::setValue);
    connect(slider3, &QSlider::valueChanged, this , &ControlPanelWidget::setY2);
    connect(spinbox3, SIGNAL(valueChanged(int)), slider3, SLOT(setValue(int)));
    connect(spinbox3, SIGNAL(valueChanged(int)), this, SLOT(setValue(int)));
}

void ControlPanelWidget::setX1(int x1)
{
        X1 = x1;
        emit X1Changed(x1);
}

void ControlPanelWidget::setX2(int x2)
{
        X2 = x2;
        emit X2Changed(x2);
}

void ControlPanelWidget::setY1(int y1)
{
        Y1 = y1;
        emit Y1Changed(y1);
}

void ControlPanelWidget::setY2(int y2)
{
        Y2 = y2;
        emit Y2Changed(y2);
}

ControlPanelWidget::~ControlPanelWidget()
{

}
