#ifndef MYBOX_H
#define MYBOX_H

#include <QObject>
#include <QAbstractItemModel>
#include <QGraphicsItem>
#include <QtCore>
#include <QPainter>
#include "resources.h"

class Game; // Game holds a vector of MyBox pointers, and MyBox holds a Game pointer

class MyBox : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

public:
    explicit MyBox(QObject *parent = nullptr, Game *game = nullptr, int index = -1);
    ~MyBox();
    void resetBox();
    // Header:

    gameboard::PlayerType getValue();
private:

    gameboard::PlayerType boxStatus_;
    int boxIndex_;
    bool pressed_;
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

#endif // MYBOX_H
