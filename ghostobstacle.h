#ifndef GHOSTOBSTACLE_H
#define GHOSTOBSTACLE_H

#include "movableitem.h"

class GhostObstacle: public MovableItem
{
public:
    GhostObstacle();
    void setImage();
    void move();

private:
    Box* dest;
};

#endif // GHOSTOBSTACLE_H
