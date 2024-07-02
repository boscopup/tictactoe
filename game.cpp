#include "game.h"
#include <QObject>
#include <QDebug>
#include "resources.h"


Game::Game() {}

gameboard::PlayerType Game::getPlayerTurn()
{

}

void Game::changePlayerTurn()
{

}

void Game::addBox(MyBox *box)
{
    m_boxes.push_back(box);
}

void Game::handlePlayerSelectionMade()
{
    qDebug() << "Game::handlePlayerSelectionMade called\n";
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