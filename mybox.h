#ifndef MYBOX_H
#define MYBOX_H

#include <QObject>
#include <QAbstractItemModel>
#include <QGraphicsItem>
#include <QtCore>
#include <QPainter>

class MyBox : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

public:
    explicit MyBox(QObject *parent = nullptr, int index = -1);

    // Header:



private:
    enum BoxStatus {x, o, none};
    BoxStatus boxStatus_;
    int boxIndex_;
    bool pressed_;

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
