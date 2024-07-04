#include "board.h"
#include "resources.h"
#include <QPen>
#include <QGraphicsScene>

Board::Board()
{
    this->setRect(0,0,gameboard::board_width, gameboard::board_width);
    setAcceptedMouseButtons(Qt::NoButton);
}


QRectF Board::boundingRect() const
{
    return QRectF(0,0,gameboard::board_width, gameboard::board_width);
}

void Board::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen;
    pen.setCapStyle(Qt::RoundCap);
    pen.setWidth(10);
    painter->setPen(pen);

    // Top horizontal line
    QLine line1(0, gameboard::box1_end, gameboard::board_width-5, gameboard::box1_end);

    // Bottom horizontal line
    QLine line2(0, gameboard::box2_end, gameboard::board_width-5, gameboard::box2_end);

    // Left vertical line
    QLine line3(gameboard::box1_end, 0, gameboard::box1_end, gameboard::board_width-5);

    // Right vertical line
    QLine line4(gameboard::box2_end, 0, gameboard::box2_end, gameboard::board_width-5);

    painter->drawLine(line1);
    painter->drawLine(line2);
    painter->drawLine(line3);
    painter->drawLine(line4);
}


void Board::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "Board mouse press event called\n";
}

void Board::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "Board mouse release event called\n";
}
