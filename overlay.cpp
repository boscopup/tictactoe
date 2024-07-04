#include "overlay.h"
#include "resources.h"
#include <map>
#include <QPen>
#include <QPainter>

Overlay::Overlay() {
    m_lines["row1"] = false;
    m_lines["row2"] =false;
    m_lines["row3"] = false;
    m_lines["col1"] = false;
    m_lines["col2"] = false;
    m_lines["col3"] = false;
    m_lines["diag1"] = false;
    m_lines["diag2"] = false;
}


QRectF Overlay::boundingRect() const
{
    return QRectF(0,0,gameboard::board_width, gameboard::board_width);
}

void Overlay::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen;
    pen.setCapStyle(Qt::RoundCap);
    pen.setWidth(5);
    pen.setColor(Qt::red);

    painter->setPen(pen);
    if (m_lines["row1"]) {
        painter->drawLine(0, gameboard::box1_end / 2, gameboard::board_width, gameboard::box1_end / 2);
    }
    if (m_lines["row2"]) {
        painter->drawLine(0, gameboard::box2_end - gameboard::box_width / 2, gameboard::board_width, gameboard::box2_end - gameboard::box_width / 2);
    }
    if (m_lines["row3"]) {
        painter->drawLine(0, gameboard::box3_end - gameboard::box_width / 2, gameboard::board_width, gameboard::box3_end - gameboard::box_width / 2);
    }
    if (m_lines["col1"]) {
        painter->drawLine(gameboard::box1_end / 2, 0, gameboard::box1_end / 2, gameboard::board_width);
    }
    if (m_lines["col2"]) {
        painter->drawLine(gameboard::box2_end - gameboard::box_width / 2, 0, gameboard::box2_end - gameboard::box_width / 2, gameboard::board_width);
    }
    if (m_lines["col3"]) {
        painter->drawLine(gameboard::box3_end - gameboard::box_width / 2, 0, gameboard::box3_end - gameboard::box_width / 2, gameboard::board_width);
    }
    if (m_lines["diag1"]) {
        painter->drawLine(0, 0, gameboard::board_width, gameboard::board_width);
    }
    if (m_lines["diag2"]) {
        painter->drawLine(gameboard::board_width, 0, 0, gameboard::board_width);
    }
}

void Overlay::setLines(std::map<QString, bool> &lines)
{
    std::map<QString, bool>::iterator it;
    for (it = lines.begin(); it != lines.end(); it++) {
        m_lines[it->first] = it->second;
    }
}

void Overlay::clearLines()
{
    std::map<QString, bool>::iterator it;
    for (it = m_lines.begin(); it != m_lines.end(); it++) {
        m_lines[it->first] = false;
    }
}
