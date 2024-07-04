#ifndef BOARD_H
#define BOARD_H

#include <QGraphicsRectItem>
#include <QPainter>
#include <QObject>

class Board : public QGraphicsRectItem, public QObject
{
public:
    Board();

    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    // QGraphicsItem interface
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // Board_H
