#include "box.h"
#include <QtCore>
#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include <QFont> // Won't need this later
#include "resources.h"
#include "game.h"

Box::Box(QObject *parent, Game *game, int index)
{
    m_game = game;
    int x = 0;
    int y = 0;

    m_boxIndex = index;
    boxStatus_ = gameboard::none;

    // For boxes 1-3, y is box1_start
    // For boxes 4-6, y is box2_start
    // For boxes 7-9, y is box3_start
    switch (index) {
    case 1:
    case 2:
    case 3:
        y = gameboard::box1_start;
        break;
    case 4:
    case 5:
    case 6:
        y = gameboard::box2_start;
        break;
    case 7:
    case 8:
    case 9:
        y = gameboard::box3_start;
        break;
    }

    // For boxes 1, 4, 7, x is box1_start
    // For boxes 2, 5, 8, x is box2_start
    // For boxes 3, 6, 9, x is box3_start
    switch (index) {
    case 1:
    case 4:
    case 7:
        x = gameboard::box1_start;
        break;
    case 2:
    case 5:
    case 8:
        x = gameboard::box2_start;
        break;
    case 3:
    case 6:
    case 9:
        x = gameboard::box3_start;
        break;
    }

    // Account for borders, even though I thought I'd already accounted for those
    x -= 5;
    y -= 5;

    setPos(mapToParent(x,y));
    setFlag(ItemIsSelectable);
}

Box::~Box()
{
    qDebug()<< "Deleting box " << m_boxIndex << "\n";
}

void Box::resetBox()
{
    boxStatus_ = gameboard::none;
    update();
}

gameboard::PlayerType Box::getValue()
{
    return boxStatus_;
}

QRectF Box::boundingRect() const
{
    return QRectF(0, 0, gameboard::box_width, gameboard::box_width);
}

void Box::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRect rec = this->boundingRect().toRect();
    switch(boxStatus_) {
    case gameboard::none:
        painter->eraseRect(rec);
        break;
    case gameboard::x:
        painter->drawPixmap(rec, *Game::xImage);
        break;
    case gameboard::o:
        painter->drawPixmap(rec, *Game::oImage);
        break;
    }
}

void Box::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_pressed = true;
}

void Box::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_pressed) {
        m_pressed = false;
        if (Game::getPlayerTurn() == gameboard::x) {
            boxStatus_ = gameboard::x;
        } else {
            boxStatus_ = gameboard::o;
        }
        m_game->changePlayerTurn();
        update();
        emit handleBoxChangedEvent();
    }
}
