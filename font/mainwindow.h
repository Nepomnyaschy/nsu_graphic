#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <drawwidget.h>
#include <controlpanelwidget.h>
#include <QHBoxLayout>
#include <QMouseEvent>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    DrawWidget *drawwidget;
    ControlPanelWidget *controlpanelwidget;
    QHBoxLayout *layout;
    void saveConfig();
    void loadConfig();
    void saveImage();

};

#endif // MAINWINDOW_H
