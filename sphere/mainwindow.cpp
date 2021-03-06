#include "mainwindow.h"
#include "config.h"

#include <QMenuBar>
#include <QAction>
#include <QFileDialog>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QByteArray>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    drawwidget = new DrawWidget(this);
    controlpanelwidget = new ControlPanelWidget(this);
    layout = new QHBoxLayout(this);
    auto centralWidget = new QWidget(this);

    setMinimumHeight(400);
    setMinimumWidth(400);
    setCentralWidget(centralWidget);
    resize(1200, 720);
    this->setMouseTracking(true);
    drawwidget->setMouseTracking(true);

    layout->addWidget(drawwidget);
    layout->addWidget(controlpanelwidget, 0 , Qt::AlignTop);

    centralWidget->setLayout(layout);

    auto menu = menuBar();
    menu->addMenu(tr("File"));

    auto actionLoad = new QAction(tr("Load"), menu);
    auto actionSave = new QAction(tr("Save"), menu);
    auto actionToPicture = new QAction(tr("png"), menu);

    menu->addAction(actionSave);
    menu->addAction(actionLoad);
    menu->addAction(actionToPicture);

    connect(actionSave, &QAction::triggered, this, &MainWindow::saveConfig);
    connect(actionLoad, &QAction::triggered, this, &MainWindow::loadConfig);
    connect(actionToPicture, &QAction::triggered, this, &MainWindow::saveImage);

    connect(controlpanelwidget, &ControlPanelWidget::XChanged, drawwidget , &DrawWidget::setX);
    connect(controlpanelwidget, &ControlPanelWidget::YChanged, drawwidget , &DrawWidget::setY);
    connect(controlpanelwidget, &ControlPanelWidget::ScaleChanged, drawwidget , &DrawWidget::setScale);
    connect(controlpanelwidget, &ControlPanelWidget::FilterChanged, drawwidget, &DrawWidget::setFilter);

    connect(controlpanelwidget, &ControlPanelWidget::XChanged, controlpanelwidget->spinbox , &QSpinBox::setValue);
    connect(controlpanelwidget, &ControlPanelWidget::YChanged, controlpanelwidget->spinbox1 , &QSpinBox::setValue);
    connect(controlpanelwidget, &ControlPanelWidget::ScaleChanged, controlpanelwidget->spinbox2 , &QSpinBox::setValue);

    connect(drawwidget, SIGNAL(glyphShifted(QPoint)), controlpanelwidget, SLOT(shift(QPoint)));
}

void MainWindow::loadConfig()
{
   /* QString fileName = QFileDialog::getOpenFileName(
        this, tr("Load file"), QDir::currentPath(), tr("All files (*.json)")
    );
    if (fileName.isEmpty()) return;
    QMap<QString, int> configMap;
    Config::loadJson(fileName, configMap);

    drawwidget->resize(configMap["width"], configMap["height"]);
    drawwidget->setX1(configMap["x1"]);
    drawwidget->setX2(configMap["x2"]);
    drawwidget->setY1(configMap["y1"]);
    drawwidget->setY2(configMap["y2"]);*/
}

void MainWindow::saveImage()
{
    QString filename = QFileDialog::getSaveFileName(
                this, tr("save image"), QDir::currentPath(), tr("All files (*.png)"));

    if(filename.isEmpty()) return;

    drawwidget->savePicture(filename);

}

void MainWindow::saveConfig()
{
    /*QString filename = QFileDialog::getSaveFileName(
                this, tr("save file"), QDir::currentPath(), tr("All files (*.json)"));

    if(filename.isEmpty()) return;

    QFile savefile(filename);
    savefile.open(QFile::WriteOnly | QFile::Text);

    auto jsonDocument = Config::saveJson(controlpanelwidget->getX1(),
                                         controlpanelwidget->getX2(),
                                         controlpanelwidget->getY1(),
                                         controlpanelwidget->getY2(),
                                         drawwidget->height(),
                                         drawwidget->width());
    savefile.write(jsonDocument->toJson());*/

}


MainWindow::~MainWindow()
{

}
