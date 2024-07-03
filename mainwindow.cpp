#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <vector>
#include "resources.h"
#include <QDebug>
#include <QObject>
#include "game.h"
#include <QGraphicsScene>
#include <QMessageBox>
#include <QPushButton>
#include "myscene.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    playerTurnScene = new QGraphicsScene(this);
    ui->GV_currentPlayer->setScene(playerTurnScene);

    // Initialize game board
    game = new Game();
    playerTurnScene->addPixmap(*Game::xImage);
    scene = new MyScene(this, game);
    connect(game, &Game::updateParentPlayerDisplay, this, &MainWindow::updatePlayerDisplay);
    connect(game, &Game::endRound, this, &MainWindow::endRound);
    ui->GV_gameBoard->setScene(scene);
    board = new MyBoard();
    scene->setSceneRect(board->boundingRect());
    scene->addItem(board);


    // Set up the 9 boxes where the X and O will go
    MyBox* box;
    int boxIndex = 1;
    for (int i = 0; i < 9; i++) {
        box = new MyBox(scene, game, i+1);
        game->addBox(box);
        scene->addItem(box);
        connect(box, &MyBox::handleBoxChangedEvent, game, &Game::handlePlayerSelectionMade);
    }
}

MainWindow::~MainWindow()
{
    delete playerTurnScene;
    delete scene;
    delete board;
    delete game;
    delete ui;

}

void MainWindow::exitGame()
{
    QCoreApplication::quit();
}

void MainWindow::updatePlayerDisplay(QPixmap *img)
{
    qDebug() << "MainWindow updatePlayerDisplay called\n";
    playerTurnScene->clear();
    playerTurnScene->addPixmap(*img);
    ui->GV_currentPlayer->setScene(playerTurnScene);
    ui->GV_currentPlayer->show();

}

void MainWindow::endRound(gameboard::PlayerType winner)
{
    qDebug() << "Round over\n";
    // Update player scores
    // Pop up dialog with winner to see if they want to play again, otherwise exit
    QMessageBox msgBox;
    QString msg;
    QPixmap *img;
    if (winner == gameboard::x) {
        msg = "X won!";
        img = Game::xImage;
    } else {
        msg = "O won!";
        img = Game::oImage;
    }
    msgBox.setText(msg);
    msgBox.setInformativeText("Would you like to play another round?");
    msgBox.setIconPixmap(*img);
    QPushButton *anotherRoundButton = msgBox.addButton(tr("Another Round"), QMessageBox::AcceptRole);
    QPushButton *resetGameButton = msgBox.addButton(tr("Reset Game"), QMessageBox::AcceptRole);
    QPushButton *exitButton = msgBox.addButton(tr("Exit Game"), QMessageBox::AcceptRole);
    msgBox.exec();

    if (msgBox.clickedButton() == anotherRoundButton) {
        // Play another round
        qDebug() << "Play another round\n";
        delete anotherRoundButton;
        delete resetGameButton;
        delete exitButton;
    } else if (msgBox.clickedButton() == resetGameButton) {
        // Reset the game
        qDebug() << "Reset the game\n";
        delete anotherRoundButton;
        delete resetGameButton;
        delete exitButton;
    } else if (msgBox.clickedButton() == exitButton) {
        // Exit the game
        qDebug() << "Exit the game\n";
        delete anotherRoundButton;
        delete resetGameButton;
        delete exitButton;
        exitGame();
    }
}
