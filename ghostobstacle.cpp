#include "ghostobstacle.h"
#include "game.h"
#include <QDebug>

extern Game* game;
GhostObstacle::GhostObstacle()
{
    name = "obstacler";
    setScale(0.045);
    setZValue(5);
    setImage();
    nodeInitialize();

    dest = nullptr;
}

void GhostObstacle::setImage(){
    setPixmap(QPixmap(":/new/prefix1/imgs/bomber.png"));
}


void GhostObstacle::move(){
    srand(static_cast<unsigned int>(time(nullptr)));
    if(obstacleChoice.size()==0)return;
    if(dest==currentBox || dest==nullptr){
        int n = obstacleChoice.size();
        int i = rand()%n;
        dest = obstacleChoice[i];
    }

    searchNext(dest);
    currentBox->currentGhost4 = nullptr;
    nextMove->ghost4PlaceIn(this);

}
