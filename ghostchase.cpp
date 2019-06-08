#include "ghostchase.h"
#include "game.h"
#include <QDebug>

extern Game* game;
GhostChase::GhostChase()
{
    name = "chaser";
    setScale(0.045);
    setZValue(5);
    setImage();
    nodeInitialize();

}

void GhostChase::setImage(){
    setPixmap(QPixmap(":/new/prefix1/imgs/angel.png"));
}

void GhostChase::move(){
    int row = game->getMap()->pacman->getRow();
    int col = game->getMap()->pacman->getCol();

    searchNext(game->getMap()->boxes[row][col]);
    currentBox->currentGhost1 = nullptr;
    nextMove->ghost1PlaceIn(this);
}
