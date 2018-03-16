#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class GameController;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    GameController *game;
};

#endif // MAINWINDOW_H
