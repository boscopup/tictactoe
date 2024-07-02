#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <vector>
#include "resources.h"
#include <QDebug>
#include <QObject>
#include "game.h"
#include <QGraphicsScene>
#include "myscene.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialize game board
    game = new Game();
    scene = new MyScene(this, game);
    ui->GV_gameBoard->setScene(scene);
    board = new MyBoard();
    scene->setSceneRect(board->boundingRect());
    scene->addItem(board);


    // Set up the 9 boxes where the X and O will go
    MyBox* box;
    int boxIndex = 1;
    for (int i = 0; i < 9; i++) {
        box = new MyBox(scene, i+1);
        game->addBox(box);
        scene->addItem(box);
        connect(box, &MyBox::handleBoxChangedEvent, game, &Game::handlePlayerSelectionMade);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
