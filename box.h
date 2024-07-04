#ifndef BOX_H
#define BOX_H

#include <QObject>
#include <QAbstractItemModel>
#include <QGraphicsItem>
#include <QtCore>
#include <QPainter>
#include "resources.h"

class Game; // Game holds a vector of Box pointers, and Box holds a Game pointer

class Box : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

public:
    explicit Box(QObject *parent = nullptr, Game *game = nullptr, int index = -1);
    ~Box();
    void resetBox();
    // Header:

    gameboard::PlayerType getValue();
private:

    gameboard::PlayerType boxStatus_;
    int m_boxIndex;
    bool m_pressed;
    Game *m_game;       // Contents of pointer are deleted in ~MainWindow destructor

    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

public:
signals:
    void handleBoxChangedEvent();

    // QGraphicsItem interface
};

#endif // Box_H
