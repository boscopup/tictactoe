#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <vector>
#include "board.h"
#include "box.h"
#include "game.h"
#include "resources.h"
#include "scene.h"
#include "overlay.h"

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
    Scene *scene;
    Board *board;
    Overlay *overlay;
    Game *game;

    void exitGame();
    void resetGame();
    void resetRound();

public slots:
    void updatePlayerDisplay(QPixmap *img);
    void endRound(gameboard::PlayerType winner);
};
#endif // MAINWINDOW_H
