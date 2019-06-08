#include "ghostambush1.h"
#include "game.h"
#include <QDebug>

extern Game* game;
GhostAmbush1::GhostAmbush1()
{
    name = "ambusher1";
    setScale(0.045);
    setZValue(5);
    setImage();
    nodeInitialize();

}

void GhostAmbush1::setImage(){
    setPixmap(QPixmap(":/new/prefix1/imgs/mouse.png"));
}

void GhostAmbush1::move(){
    int pac_row = game->getMap()->pacman->getRow();
    int pac_col = game->getMap()->pacman->getCol();
    int ghost1_row = game->getMap()->ghost1->getRow();
    int ghost4_row = game->getMap()->ghost4->getRow();
    int my_row = currentBox->rowLoc;
    int my_col = currentBox->colLoc;

    if( game->getGhost1Flag() && ((pac_row>ghost1_row && my_row>=pac_row) || (pac_row<ghost1_row && my_row<=pac_row))){
        searchNext(game->getMap()->boxes[pac_row][pac_col]);
        currentBox->currentGhost2 = nullptr;
        nextMove->ghost2PlaceIn(this);
    }
    else if( game->getGhost4Flag() && ((pac_row>ghost4_row && my_row>=pac_row) || (pac_row<ghost4_row && my_row<=pac_row))){
        searchNext(game->getMap()->boxes[pac_row][pac_col]);
        currentBox->currentGhost2 = nullptr;
        nextMove->ghost2PlaceIn(this);
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
            currentBox->currentGhost2 = nullptr;
            game->getMap()->boxes[my_row-1][my_col]->ghost2PlaceIn(this);
            break;
        case 2:
            currentBox->currentGhost2 = nullptr;
            game->getMap()->boxes[my_row+1][my_col]->ghost2PlaceIn(this);
            break;
        case 3:
            currentBox->currentGhost2 = nullptr;
            game->getMap()->boxes[my_row][my_col-1]->ghost2PlaceIn(this);
            break;
        case 4:
            currentBox->currentGhost2 = nullptr;
            game->getMap()->boxes[my_row][my_col+1]->ghost2PlaceIn(this);
            break;
        }
    }
}
