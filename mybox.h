#ifndef MYBOX_H
#define MYBOX_H

#include <QObject>
#include <QAbstractItemModel>
#include <QGraphicsItem>
#include <QtCore>
#include <QPainter>

class MyBox : public QObject, public QGraphicsRectItem
{

public:
    explicit MyBox(QObject *parent = nullptr, int index = -1);

    // Header:



private:
    enum BoxStatus {x, o, none};
    BoxStatus boxStatus_;
    int boxIndex_;

    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // MYBOX_H
