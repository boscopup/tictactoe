#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <vector>
#include "myboard.h"
#include "mybox.h"
#include "game.h"
#include "resources.h"
#include "myscene.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *playerTurnScene;
    MyScene *scene;
    MyBoard *board;
    Game *game;
public slots:
    void updatePlayerDisplay(QPixmap *img);
};
#endif // MAINWINDOW_H
