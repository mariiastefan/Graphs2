#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include "graph.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    virtual void paintEvent(QPaintEvent *event);
    virtual void paths(std::vector<bool> pathnode, int n, std::vector<std::vector<int>>& matrix);
    virtual void cycles(std::vector<bool> cyclenode, int n, std::vector<std::vector<int>>& matrix);
private:
    Ui::MainWindow *ui;
    Graph g;
};
#endif // MAINWINDOW_H
