#ifndef MYBOARD_H
#define MYBOARD_H

#include <QGraphicsRectItem>
#include <QPainter>
#include <QObject>

class MyBoard : public QGraphicsRectItem, public QObject
{
public:
    MyBoard();

    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    // QGraphicsItem interface
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // MYBOARD_H
