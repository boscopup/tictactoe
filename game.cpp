#include "game.h"
#include <QObject>
#include <QDebug>
#include "resources.h"
#include <QPixmap>
#include <vector>

QPixmap *Game::xImage = nullptr;
QPixmap *Game::oImage = nullptr;
gameboard::PlayerType Game::m_playerTurn = gameboard::x;

Game::Game() {
    loadImages();
    initializeMembers();
}

Game::~Game()
{
    delete xImage;
    delete oImage;
    for (std::vector<MyBox *>::iterator iter = m_boxes.begin(); iter != m_boxes.end();) {
        delete *iter;
        m_boxes.erase(iter);    // Don't need to increase iter due to erase
    }
}

void Game::resetBoard()
{
    // TODO: Remove any lines drawn (lines aren't drawn yet)

    // Reset boxes
    for (std::vector<MyBox *>::iterator it = m_boxes.begin(); it != m_boxes.end(); it++) {
        (*it)->resetBox();
    }

    // Set current player to X
    m_playerTurn = gameboard::x;
    m_winner = gameboard::none;

}

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

    if ((one != gameboard::none) && (one == two) && (two == three)) {
        m_lines[Lines::row1] = true;
        m_winner = one;
    }
    if ((four != gameboard::none) && (four == five) && (five == six)) {
        m_lines[Lines::row2] = true;
        m_winner = four;
    }
    if ((seven != gameboard::none) && (seven == eight) && (eight == nine)) {
        m_lines[Lines::row3] = true;
        m_winner = seven;
    }
    if ((one != gameboard::none) && (one == four) && (four == seven)) {
        m_lines[Lines::col1] = true;
        m_winner = one;
    }
    if ((two != gameboard::none) && (two == five) && (five == eight)) {
        m_lines[Lines::col2] = true;
        m_winner = two;
    }
    if ((three != gameboard::none) && (three == six) && (six == nine)) {
        m_lines[Lines::col3] = true;
        m_winner = three;
    }
    if ((one != gameboard::none) && (one == five) && (five == nine)) {
        m_lines[Lines::diag1] = true;
        m_winner = one;
    }
    if ((three != gameboard::none) && (three == five) && (five == seven)) {
        m_lines[Lines::diag2] = true;
        m_winner = three;
    }

    if (m_winner != gameboard::none) {
        // TODO: Draw line(s) across winning row/col/diag
        emit endRound(m_winner);
    }
    return false;

}

void Game::initializeMembers()
{
    m_winner = gameboard::none;
    m_lines[Lines::row1] = false;
    m_lines[Lines::row2] = false;
    m_lines[Lines::row3] = false;
    m_lines[Lines::col1] = false;
    m_lines[Lines::col2] = false;
    m_lines[Lines::col3] = false;
    m_lines[Lines::diag1] = false;
    m_lines[Lines::diag2] = false;
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
