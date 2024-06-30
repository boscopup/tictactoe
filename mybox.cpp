#include "mybox.h"
#include <QtCore>
#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include <QFont> // Won't need this later
#include "resources.h"

// 1   2   3
// 4   5   6
// 7   8   9



MyBox::MyBox(QObject *parent, int index)
{
    int x,y;

    boxIndex_ = index;

    this->setParent(parent);

    // For boxes 1-3, y is box1_start
    // For boxes 4-6, y is box2_start
    // For boxes 7-9, y is box3_start
    switch (index) {
    case 1:
    case 2:
    case 3:
        y = gameboard::box1_start;
        break;
    case 4:
    case 5:
    case 6:
        y = gameboard::box2_start;
        break;
    case 7:
    case 8:
    case 9:
        y = gameboard::box3_start;
        break;
    }

    // For boxes 1, 4, 7, x is box1_start
    // For boxes 2, 5, 8, x is box2_start
    // For boxes 3, 6, 9, x is box3_start
    switch (index) {
    case 1:
    case 4:
    case 7:
        x = gameboard::box1_start;
        break;
    case 2:
    case 5:
    case 8:
        x = gameboard::box2_start;
        break;
    case 3:
    case 6:
    case 9:
        x = gameboard::box3_start;
        break;
    }

    // Account for borders, even though I thought I'd already accounted for those
    x -= 5;
    y -= 5;

    qDebug() << "x=" << x << ", y=" << y;
    setPos(mapToParent(x,y));
}



QRectF MyBox::boundingRect() const
{
    return QRectF(0, 0, gameboard::box_width, gameboard::box_width);
}

void MyBox::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = this->boundingRect();
    QBrush brush(Qt::blue);
    QPen pen;
    QFont font = painter->font();

    pen.setWidth(0);
    painter->setBrush(brush);
    painter->setPen(pen);
    painter->drawRect(rec);
    pen.setWidth(3);
    pen.setColor(Qt::black);
    painter->setPen(pen);
    font.setPointSize(16);
    painter->setFont(font);
    painter->drawText(rec, QString::number(boxIndex_));
}

void MyBox::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
}

void MyBox::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
}
