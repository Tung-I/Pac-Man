#ifndef BOX_H
#define BOX_H

#include <QGraphicsRectItem>
#include <QBrush>
#include "eatableitem.h"
#include "movableitem.h"
#include "wall.h"


class Box : public QGraphicsRectItem
{
public:
    Box(QGraphicsItem *parent = nullptr);
    void pacPlaceIn(MovableItem * item);
    void ghost1PlaceIn(MovableItem * item);
    void ghost2PlaceIn(MovableItem * item);
    void ghost3PlaceIn(MovableItem * item);
    void ghost4PlaceIn(MovableItem * item);
    void setCurrentPac(MovableItem *currentPac);
    int rowLoc;
    int colLoc;

    MovableItem *currentPac;
    MovableItem *currentGhost1;
    MovableItem *currentGhost2;
    MovableItem *currentGhost3;
    MovableItem *currentGhost4;
    EatableItem *currentDot;
    Wall *currentWall;
private:
    QBrush _brush;
    QPen pen;


};

#endif // BOX_H
