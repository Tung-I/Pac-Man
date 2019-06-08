#include "ghostambush2.h"
#include "game.h"
#include <QDebug>

extern Game* game;
GhostAmbush2::GhostAmbush2()
{
    name = "ambusher2";
    setScale(0.045);
    setZValue(5);
    setImage();
    nodeInitialize();

}

void GhostAmbush2::setImage(){
    setPixmap(QPixmap(":/new/prefix1/imgs/penguin.png"));
}

void GhostAmbush2::move(){
    int pac_row = game->getMap()->pacman->getRow();
    int pac_col = game->getMap()->pacman->getCol();
    int ghost1_col = game->getMap()->ghost1->getCol();
    int ghost4_col = game->getMap()->ghost4->getCol();
    int my_row = currentBox->rowLoc;
    int my_col = currentBox->colLoc;

    if( game->getGhost1Flag() && ((pac_col>ghost1_col && my_col>=pac_col) || (pac_col<ghost1_col && my_col<=pac_col))){
        searchNext(game->getMap()->boxes[pac_row][pac_col]);
        currentBox->currentGhost3 = nullptr;
        nextMove->ghost3PlaceIn(this);
    }
    else if( game->getGhost4Flag() && ((pac_col>ghost4_col && my_col>=pac_col) || (pac_col<ghost4_col && my_col<=pac_col))){
        searchNext(game->getMap()->boxes[pac_row][pac_col]);
        currentBox->currentGhost3 = nullptr;
        nextMove->ghost3PlaceIn(this);
    }
    else{
        srand(static_cast<unsigned int>(time(nullptr)));
        int cnt = 0;
        QList<int> choice;
        if(game->getMap()->boxes[my_row-1][my_col]->currentWall==nullptr){
            choice.append(1);
            cnt++;
        }
        if(game->getMap()->boxes[my_row+1][my_col]->currentWall==nullptr){
            choice.append(2);
            cnt++;
        }
        if(game->getMap()->boxes[my_row][my_col-1]->currentWall==nullptr){
            choice.append(3);
            cnt++;
        }
        if(game->getMap()->boxes[my_row][my_col+1]->currentWall==nullptr){
            choice.append(4);
            cnt++;
        }
        int i = rand()%cnt;
        int nextDir = choice[i];
        switch(nextDir){
        case 1:
            currentBox->currentGhost3 = nullptr;
            game->getMap()->boxes[my_row-1][my_col]->ghost3PlaceIn(this);
            break;
        case 2:
            currentBox->currentGhost3 = nullptr;
            game->getMap()->boxes[my_row+1][my_col]->ghost3PlaceIn(this);
            break;
        case 3:
            currentBox->currentGhost3 = nullptr;
            game->getMap()->boxes[my_row][my_col-1]->ghost3PlaceIn(this);
            break;
        case 4:
            currentBox->currentGhost3 = nullptr;
            game->getMap()->boxes[my_row][my_col+1]->ghost3PlaceIn(this);
            break;
        }
    }
}
