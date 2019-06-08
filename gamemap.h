#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "box.h"
#include "movableitem.h"
#include "eatableitem.h"
#include "pacman.h"
#include "ghostchase.h"
#include "ghostambush1.h"
#include "ghostambush2.h"
#include "ghostobstacle.h"
#include "wall.h"
#include "eatableitem.h"

class GameMap
{
    friend class Game;
public:
    GameMap();
    void drawBox(int x, int y);
    void drawWall(int x_l, int x_r, int y_u, int y_d);
    void drawAllWall();
    void drawDot();
    void reset();
    int getDotLeft();
    void reduceDotLeft();

    void drawPac(int rol, int col);
    void drawGhost1(int, int);
    void drawGhost2(int, int);
    void drawGhost3(int, int);
    void drawGhost4(int, int);

    void resetGhost1();
    void resetGhost2();
    void resetGhost3();
    void resetGhost4();



    //boxes
    Box *boxes[31][28];

    //character
    MovableItem *pacman;
    MovableItem *ghost1;
    MovableItem *ghost2;
    MovableItem *ghost3;
    MovableItem *ghost4;

private:
    QPainter *painter;
    QList <EatableItem*> dotList;
    int dotLeft;

};

#endif // GAMEMAP_H
