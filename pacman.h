#ifndef PACMAN_H
#define PACMAN_H

#include "movableitem.h"

class Pacman : public MovableItem
{
public:
    Pacman();
    void setImage();
    void move();
    void goUp();
    void goDown();
    void goLeft();
    void goRight();
};

#endif // PACMAN_H
