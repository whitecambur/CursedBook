#include <QGraphicsView>
#include <QGridLayout>
#include "common.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      game(new GameController(this, this))
{
    setMouseTracking(true);
    setMinimumSize(480,310);
    resize(1000,620);
}

MainWindow::~MainWindow()
{

}
void MainWindow::paintEvent(QPaintEvent *event){
    QPainter MyPainter(this);
    game->Show(&MyPainter,width(),height());
}


