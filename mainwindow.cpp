#include "mainwindow.h"


#include <QMenuBar>
#include <QAction>
#include <QFileDialog>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QByteArray>

QJsonDocument* saveJson(int x, int y, int r, int height, int width);


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    printf("Hello");
    drawwidget = new DrawWidget(this);
    controlpanelwidget = new ControlPanelWidget(this);
    layout = new QHBoxLayout(this);
    auto centralWidget = new QWidget(this);

    setCentralWidget(centralWidget);
    resize(800, 600);

    layout->addWidget(drawwidget);
    layout->addWidget(controlpanelwidget, 0 , Qt::AlignTop);

    centralWidget->setLayout(layout);

    auto menu = menuBar();
    menu->addMenu(tr("File"));

    auto actionLoad = new QAction(tr("Load"), menu);
    auto actionSave = new QAction(tr("Save"), menu);

    menu->addAction(actionSave);
    menu->addAction(actionLoad);

    connect(actionSave, &QAction::triggered, this, &MainWindow::saveConfig);

    connect(controlpanelwidget, &ControlPanelWidget::RChanged, drawwidget , &DrawWidget::setR);
    connect(controlpanelwidget, &ControlPanelWidget::XChanged, drawwidget , &DrawWidget::setX);
    connect(controlpanelwidget, &ControlPanelWidget::YChanged, drawwidget , &DrawWidget::setY);
}

void MainWindow::saveConfig()
{
    QString filename = QFileDialog::getSaveFileName(
                this, tr("save file"), QDir::currentPath(), tr(".json"));

    if(filename.isEmpty()) return;

    QFile savefile(filename);
    savefile.open(QFile::WriteOnly | QFile::Text);

    auto jsonDocument = saveJson(controlpanelwidget->getX(),
                                 controlpanelwidget->getY(),
                                 controlpanelwidget->getR(),
                                 drawwidget->height(),
                                 drawwidget->width());
    savefile.write(jsonDocument->toJson());

}

QJsonDocument* saveJson(int x, int y, int r, int height, int width)
{
    QJsonObject jsonObject;
    QJsonArray jsonCircles;
    QJsonObject jsonPosition;
    QJsonObject jsonPanel;
    QJsonObject jsonSize;
    QJsonObject jsonCircle;

    jsonPosition["x"] = x;
    jsonPosition["y"] = y;
    jsonCircle["r"] = r;
    jsonCircle["position"] = jsonPosition;
    jsonCircles.append(jsonCircle);

    jsonSize["x"] = height;
    jsonSize["y"] = width;
    jsonPanel["size"] = jsonSize;

    jsonObject["circles"] = jsonCircles;
    jsonObject["panel"] = jsonPanel;

    return new QJsonDocument(jsonObject);

}

MainWindow::~MainWindow()
{

}
