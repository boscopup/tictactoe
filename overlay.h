#ifndef OVERLAY_H
#define OVERLAY_H

#include <QGraphicsRectItem>
#include <QObject>
#include <map>

class Overlay : public QGraphicsRectItem
{
private:
    std::map<QString, bool> m_lines;

public:
    Overlay();

    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setLines(std::map<QString, bool> &lines);
    void clearLines();
};

#endif // OVERLAY_H
