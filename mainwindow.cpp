#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <vector>
#include "resources.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialize game board
    scene = new QGraphicsScene(this);
    ui->GV_gameBoard->setScene(scene);
    board = new MyBoard();
    scene->setSceneRect(board->boundingRect());
    scene->addItem(board);

    // Set up the 9 boxes where the X and O will go
    // TODO
    MyBox* box;
    int boxIndex = 1;    for (int i = 0; i < 9; i++) {
            box = new MyBox(board, i+1);
            boxes.push_back(box);
            scene->addItem(box);


    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
