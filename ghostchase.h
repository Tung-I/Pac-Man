#ifndef GHOST_CHASE_H
#define GHOST_CHASE_H

#include "movableitem.h"

class GhostChase: public MovableItem
{
public:
    GhostChase();
    void setImage();
    void move();
};

#endif // GHOST_CHASE_H
