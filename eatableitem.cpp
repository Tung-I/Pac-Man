#include "eatableitem.h"

EatableItem::EatableItem(bool pellet) : QGraphicsEllipseItem()
{
    //set size and color
    if(pellet)setRect(0,0,15,15);
    else setRect(0,0,7,7);

    itemColor = Qt::yellow;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(itemColor);
    setBrush(brush);

    setZValue(3);

    //initilaize
    setPellet(pellet);
}

void EatableItem::change2Pellet(){
    powerPellet = true;
    setRect(0, 0, 15, 15);
}

void EatableItem::setPellet(bool val){powerPellet=val;}
bool EatableItem::getPellet(){return powerPellet;}
