#ifndef MYSCENE_H
#define MYSCENE_H

#include <QGraphicsScene>
#include "game.h"

class MyScene : public QGraphicsScene
{
    Q_OBJECT

private:
    Game *m_game;       // Contents of pointer are deleted in ~MainWindow destructor
public:
    explicit MyScene(QObject *parent = nullptr, Game *game = nullptr);

    // QGraphicsScene interface
protected:



    // QGraphicsScene interface
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // MYSCENE_H
