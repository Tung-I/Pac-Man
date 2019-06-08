#include "box.h"

Box::Box(QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
    setRect(0,0,25,25);
    _brush.setStyle(Qt::SolidPattern);
    _brush.setColor(QColor(10, 10, 10, 255));
    this->setBrush(_brush);

    pen.setWidth(1);
    pen.setColor(QColor(10, 10, 10, 255));
    setPen(pen);

    setZValue(1);

    currentDot = nullptr;
    currentWall = nullptr;
    currentPac = nullptr;
    currentGhost1 = nullptr;

}

void Box::pacPlaceIn(MovableItem * item){
    item->setPos(x(), y());
    currentPac = item;
    item->currentBox = this;
}
void Box::ghost1PlaceIn(MovableItem * item){
    item->setPos(x(), y());
    currentGhost1 = item;
    item->currentBox = this;
}
void Box::ghost2PlaceIn(MovableItem * item){
    item->setPos(x(), y());
    currentGhost2 = item;
    item->currentBox = this;
}
void Box::ghost3PlaceIn(MovableItem * item){
    item->setPos(x(), y());
    currentGhost3 = item;
    item->currentBox = this;
}
void Box::ghost4PlaceIn(MovableItem * item){
    item->setPos(x(), y());
    currentGhost4 = item;
    item->currentBox = this;
}


