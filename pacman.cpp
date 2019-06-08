#include "pacman.h"
#include "box.h"
#include "game.h"
#include "QDebug"

class Box;
extern Game *game;

Pacman::Pacman()
{
    setImage();
    setScale(0.02);
    setZValue(5);
    name = "Pacman";
}

void Pacman::setImage()
{
    setPixmap(QPixmap(":/new/prefix1/imgs/pacman_right.png"));
}

void Pacman::move(){
    //0freeze 1up 2down 3left 4right
    int row = getRow();
    int col = getCol();
    Box *nextBox;
    switch(moveDir){  
    case 1:
        nextBox = game->getMap()->boxes[row-1][col];
        //wall detection
        if(nextBox->currentWall!=nullptr)break;
        //eat the dot
        if(nextBox->currentDot!=nullptr){
            if(nextBox->currentDot->getPellet()==false){
                game->getMap()->reduceDotLeft();
                nextBox->currentDot->setVisible(false);
                nextBox->currentDot = nullptr;
                game->changeCurrentScore(game->getCurrentScore()+game->pointPerDot);
            }
            //eat the power pellet
            else if(nextBox->currentDot->getPellet()==true){
                nextBox->currentDot->setVisible(false);
                nextBox->currentDot = nullptr;
                game->startPowerTimer(10, 500);
            }
        }
        goUp();
        break;
    case 2:
        nextBox = game->getMap()->boxes[row+1][col];
        if(nextBox->currentWall!=nullptr)break;
        if(nextBox->currentDot!=nullptr){
            if(nextBox->currentDot->getPellet()==false){
                game->getMap()->reduceDotLeft();
                nextBox->currentDot->setVisible(false);
                nextBox->currentDot = nullptr;
                game->changeCurrentScore(game->getCurrentScore()+game->pointPerDot);
            }
            else if(nextBox->currentDot->getPellet()==true){
                nextBox->currentDot->setVisible(false);
                nextBox->currentDot = nullptr;
                game->startPowerTimer(10, 500);
            }
        }
        goDown();
        break;
    case 3:
        nextBox=(col==0)?game->getMap()->boxes[row][27]:game->getMap()->boxes[row][col-1];
        if(nextBox->currentWall!=nullptr)break;
        if(nextBox->currentDot!=nullptr){
            if(nextBox->currentDot->getPellet()==false){
                game->getMap()->reduceDotLeft();
                nextBox->currentDot->setVisible(false);
                nextBox->currentDot = nullptr;
                game->changeCurrentScore(game->getCurrentScore()+game->pointPerDot);
            }
            else if(nextBox->currentDot->getPellet()==true){
                nextBox->currentDot->setVisible(false);
                nextBox->currentDot = nullptr;
                game->startPowerTimer(10, 500);
            }
        }
        goLeft();
        break;
    case 4:
        nextBox=(col==27)?game->getMap()->boxes[row][0]:game->getMap()->boxes[row][col+1];
        if(nextBox->currentWall!=nullptr)break;
        if(nextBox->currentDot!=nullptr){
            if(nextBox->currentDot->getPellet()==false){
                game->getMap()->reduceDotLeft();
                nextBox->currentDot->setVisible(false);
                nextBox->currentDot = nullptr;
                game->changeCurrentScore(game->getCurrentScore()+game->pointPerDot);
            }
            else if(nextBox->currentDot->getPellet()==true){
                nextBox->currentDot->setVisible(false);
                nextBox->currentDot = nullptr;
                game->startPowerTimer(10, 500);
            }
        }
        goRight();
        break;

    default:
        break;
    }

}

void Pacman::goUp(){
    int row = getRow();
    int col = getCol();
    int newRow, newCol;
    currentBox->currentPac = nullptr;
    newRow = (row==0)? 30:row-1;
    newCol = col;
    game->getMap()->boxes[newRow][newCol]->pacPlaceIn(this);

    if(lastMoveDir!=1)setPixmap(QPixmap(":/new/prefix1/imgs/pacman_up.png"));
    lastMoveDir = 1;
}

void Pacman::goDown(){
    int row = getRow();
    int col = getCol();
    int newRow, newCol;
    currentBox->currentPac = nullptr;
    newRow = (row==30)? 0:row+1;
    newCol = col;
    game->getMap()->boxes[newRow][newCol]->pacPlaceIn(this);

    if(lastMoveDir!=2)setPixmap(QPixmap(":/new/prefix1/imgs/pacman_down.png"));
    lastMoveDir = 2;
}

void Pacman::goLeft(){
    int row = getRow();
    int col = getCol();
    int newRow, newCol;
    newRow = row;
    newCol = (col==0)? 27:col-1;
    currentBox->currentPac = nullptr;
    game->getMap()->boxes[newRow][newCol]->pacPlaceIn(this);

    if(lastMoveDir!=3)setPixmap(QPixmap(":/new/prefix1/imgs/pacman_left.png"));
    lastMoveDir = 3;
}

void Pacman::goRight(){
    int row = getRow();
    int col = getCol();
    int newRow, newCol;
    newRow = row;
    newCol = (col==27)? 0:col+1;
    currentBox->currentPac = nullptr;
    game->getMap()->boxes[newRow][newCol]->pacPlaceIn(this);

    if(lastMoveDir!=4)setPixmap(QPixmap(":/new/prefix1/imgs/pacman_right.png"));
    lastMoveDir = 4;
}



