#ifndef WALL_H
#define WALL_H

#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>

class Wall : public QGraphicsRectItem
{
public:
    Wall(int w, int l);

private:
     QColor wallColor;
     QBrush brush;
     QPen pen;
};

#endif // WALL_H
