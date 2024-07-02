#include "game.h"
#include <QObject>
#include <QDebug>
#include "resources.h"
#include <QPixmap>
#include "mybox.h"


QPixmap *Game::xImage = nullptr;
QPixmap *Game::oImage = nullptr;
gameboard::PlayerType Game::m_playerTurn = gameboard::x;

void Game::loadImages()
{
    if (xImage == nullptr) {
        qDebug() << "Loading xImage\n";
        xImage = new QPixmap(":/Resources/x.png");
        if (xImage->isNull()) {
            qDebug() << "Loading xImage FAILED\n";
        }
    }
    if (oImage == nullptr) {
        oImage = new QPixmap(":/Resources/o.png");
        qDebug() << "Loading oImage\n";
        if (oImage->isNull()) {
            qDebug() << "Loading oImage FAILED\n";
        }
    }
}

bool Game::isWinner()
{
    gameboard::PlayerType one, two, three, four, five, six, seven, eight, nine;
    one = m_boxes[0]->getValue();
    two = m_boxes[1]->getValue();
    three = m_boxes[2]->getValue();
    four = m_boxes[3]->getValue();
    five = m_boxes[4]->getValue();
    six = m_boxes[5]->getValue();
    seven = m_boxes[6]->getValue();
    eight = m_boxes[7]->getValue();
    nine = m_boxes[8]->getValue();

    // TODO: Add which row or col or diag won
    if ((one == two) && (one == three)) {               // row 1
        m_winner = one;
    } else if ((three == four) && (three == five)) {    // row 2
        m_winner = three;
    } else if ((seven == eight) && (seven == nine)) {   // row 3
        m_winner = seven;
    } else if ((one == four) && (one == seven)) {       // col 1
        m_winner = one;
    } else if ((two == five) && (two == eight)) {       // col 2
        m_winner = two;
    } else if ((three == 6) && (three == nine)) {       // col 3
        m_winner = three;
    } else if ((one == five) && (five == nine)) {       // diag 1
        m_winner = one;
    } else if ((three == five) && (three == seven)) {   // diag 2
        m_winner = three;
    }
    if (m_winner != gameboard::none) {
        return true;
    }
    return false;

}

Game::Game() {
    loadImages();
    m_winner = gameboard::none;
}

gameboard::PlayerType Game::getPlayerTurn()
{
    return m_playerTurn;
}

void Game::changePlayerTurn()
{
    if (m_playerTurn == gameboard::x) {
        m_playerTurn = gameboard::o;
    } else {
        m_playerTurn = gameboard::x;
    }
}

void Game::addBox(MyBox *box)
{
    m_boxes.push_back(box);
}

void Game::handlePlayerSelectionMade()
{
    qDebug() << "Game::handlePlayerSelectionMade called\n";
    // TODO: Determine is anyone has won yet or if gameboard is full
    if (isWinner()) {
        char ch;
        switch (m_winner) {
        case gameboard::x:
            ch = 'x';
            break;
        case gameboard::o:
            ch = 'o';
            break;
        }

        qDebug() << "Winner! " << ch << "\n";
    }
    // Otherwise, update the player turn display
    if (m_playerTurn == gameboard::x) {
        emit updateParentPlayerDisplay(xImage);
    } else {
        emit updateParentPlayerDisplay(oImage);
    }
}

MyBox *Game::getBox(QPointF pos)
{
    qreal x = pos.rx();
    qreal y = pos.ry();

    MyBox *box;
    if (x < gameboard::box1_end) {
        // bpxes 1, 4, or 7
        if (y < gameboard::box1_end) {
            // 1
            box = m_boxes[0];
        } else if (y < gameboard::box2_end) {
            box = m_boxes[3];
        } else {
            box = m_boxes[6];
        }
    } else if (x < gameboard::box2_end) {
        // boxes 2, 5, or 8
        if (y < gameboard::box1_end) {
            box = m_boxes[1];
        } else if (y < gameboard::box2_end) {
            box = m_boxes[4];
        } else {
            box = m_boxes[7];
        }
    } else {
        // boxes 3, 6, or 9
        if (y < gameboard::box1_end) {
            box = m_boxes[2];
        } else if (y < gameboard::box2_end) {
            box = m_boxes[5];
        } else {
            box = m_boxes[8];
        }
    }
    return box;
}
