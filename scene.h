#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include "game.h"

class Scene : public QGraphicsScene
{
    Q_OBJECT

private:
    Game *m_game;       // Contents of pointer are deleted in ~MainWindow destructor
public:
    explicit Scene(QObject *parent = nullptr, Game *game = nullptr);

    // QGraphicsScene interface
protected:



    // QGraphicsScene interface
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // Scene_H
