#include "myscene.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include "box.h"
#include "game.h"


MyScene::MyScene(QObject *parent, Game *game)
    : QGraphicsScene{parent}
{
    m_game = game;
}

void MyScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "Scene mousePressEvent\n";
    qDebug() << "Position: " << event->scenePos() << "\n";
    Box *box = m_game->getBox(event->scenePos());
    if (box->getValue() == gameboard::none) {
        box->mousePressEvent(event);
    }
}

void MyScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "Scene mouseReleaseEvent\n";
    Box *box = m_game->getBox(event->scenePos());
    if (box->getValue() == gameboard::none) {
        box->mouseReleaseEvent(event);
    }
}
