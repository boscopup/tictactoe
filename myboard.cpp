#include "myboard.h"
#include "resources.h"
#include <QPen>

MyBoard::MyBoard()
{
    this->setRect(0,0,gameboard::board_width, gameboard::board_width);

}


QRectF MyBoard::boundingRect() const
{
    return QRectF(0,0,gameboard::board_width, gameboard::board_width);
}

void MyBoard::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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
