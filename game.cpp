#include "game.h"
#include <QObject>
#include <QDebug>
#include "resources.h"
#include <QPixmap>
#include <vector>

QPixmap *Game::xImage = nullptr;
QPixmap *Game::oImage = nullptr;
QPixmap *Game::xoImage = nullptr;
gameboard::PlayerType Game::m_playerTurn = gameboard::x;

Game::Game(Overlay *overlay) {
    if (overlay != nullptr) {
        m_overlay = overlay;
    }
    loadImages();
    initializeMembers();
}

Game::~Game()
{
    delete xImage;
    delete oImage;
    delete xoImage;
    for (std::vector<Box *>::iterator iter = m_boxes.begin(); iter != m_boxes.end();) {
        delete *iter;
        m_boxes.erase(iter);    // Don't need to increase iter due to erase
    }
}

void Game::resetBoard(bool resetGame)
{
    // Reset boxes
    for (std::vector<Box *>::iterator it = m_boxes.begin(); it != m_boxes.end(); it++) {
        (*it)->resetBox();
    }

    m_winner = gameboard::none;

    if (resetGame) {
        m_startingPlayer = gameboard::x;
        m_playerTurn = gameboard::x;
    }
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
    if (xoImage == nullptr) {
        xoImage = new QPixmap(":/Resources/xo.png");
        qDebug() << "Loading xoImage\n";
        if (xoImage->isNull()) {
            qDebug() << "Loading xoImage FAILED\n";
        }
    }
}

bool Game::isWinner()
{
    std::map<QString, bool> lines =
    {
        {"row1", false},
        {"row2", false},
        {"row3", false},
        {"col1", false},
        {"col2", false},
        {"col3", false},
        {"diag1", false},
        {"diag2", false}
    };

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
        lines["row1"] = true;
        m_winner = one;
    }
    if ((four != gameboard::none) && (four == five) && (five == six)) {
        lines["row2"] = true;
        m_winner = four;
    }
    if ((seven != gameboard::none) && (seven == eight) && (eight == nine)) {
        lines["row3"] = true;
        m_winner = seven;
    }
    if ((one != gameboard::none) && (one == four) && (four == seven)) {
        lines["col1"] = true;
        m_winner = one;
    }
    if ((two != gameboard::none) && (two == five) && (five == eight)) {
        lines["col2"] = true;
        m_winner = two;
    }
    if ((three != gameboard::none) && (three == six) && (six == nine)) {
        lines["col3"] = true;
        m_winner = three;
    }
    if ((one != gameboard::none) && (one == five) && (five == nine)) {
        lines["diag1"] = true;
        m_winner = one;
    }
    if ((three != gameboard::none) && (three == five) && (five == seven)) {
        lines["diag2"] = true;
        m_winner = three;
    }

    if (m_winner != gameboard::none) {
        // TODO: Draw line(s) across winning row/col/diag
        m_overlay->setLines(lines);
        emit endRound(m_winner);
    } else {
        // Check for tie game
        if (!((one == gameboard::none) || (two == gameboard::none) || (three == gameboard::none) ||
            (four == gameboard::none) || (five == gameboard::none) || (six == gameboard::none) ||
             (seven == gameboard::none) || (eight == gameboard::none) || (nine == gameboard::none))) {
            emit endRound(m_winner);
        }
    }
    return false;

}

void Game::initializeMembers()
{
    m_winner = gameboard::none;
    m_playerTurn = gameboard::x;
    m_startingPlayer = gameboard::x;
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

void Game::changeStartingPlayer()
{
    if (m_startingPlayer == gameboard::x) {
        m_startingPlayer = gameboard::o;
        m_playerTurn = gameboard::o;
    } else {
        m_startingPlayer = gameboard::x;
        m_startingPlayer = gameboard::x;
    }
}

void Game::addBox(Box *box)
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

Box *Game::getBox(QPointF pos)
{
    qreal x = pos.rx();
    qreal y = pos.ry();

    Box *box;
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
