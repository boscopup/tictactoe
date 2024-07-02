#include "myscene.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include "mybox.h"
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
    MyBox *box = m_game->getBox(event->scenePos());
    box->mousePressEvent(event);
}

void MyScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "Scene mouseReleaseEvent\n";
    MyBox *box = m_game->getBox(event->scenePos());
    box->mouseReleaseEvent(event);
}
