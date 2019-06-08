#include "movableitem.h"
#include "box.h"
#include "game.h"
#include "node.h"
#include <QDebug>

extern Game *game;

MovableItem::MovableItem() : QGraphicsPixmapItem ()
{
    currentBox = nullptr;
    moveDir = 0;
    lastMoveDir = 0;

}
MovableItem::~MovableItem(){};

void MovableItem::changeDir(int dir){
    moveDir = dir;
}
int MovableItem::getDir(){return moveDir;}

int MovableItem::getRow(){return currentBox->rowLoc;}
int MovableItem::getCol(){return currentBox->colLoc;}

void MovableItem::nodeInitialize(){
    for(int i = 0; i < 31; i++) {
        for(int j = 0; j < 28; j++){
            Node *node = new Node();
            boxNode[i][j] = node;
        }
    }
}

void MovableItem::addDest(Box *box){
    obstacleChoice.append(box);
}

void MovableItem::searchNext(Box *dest){
    //initialize nodes
    for(int i = 0; i < 31; i++) {
        for(int j = 0; j < 28; j++){
            boxNode[i][j]->box = game->getMap()->boxes[i][j];
            boxNode[i][j]->finded = false;
            boxNode[i][j]->parent = nullptr;
            boxNode[i][j]->dist = 10000;
        }
    }

    //BFS
    QList<Node*> nodeList;
    int rowS = getRow();
    int colS = getCol();
    if(game->getMap()->boxes[rowS][colS]==dest)return;
    boxNode[rowS][colS]->finded = true;
    boxNode[rowS][colS]->parent = nullptr;
    boxNode[rowS][colS]->dist = 0;
    nodeList.push_back(boxNode[rowS][colS]);

    while(!nodeList.isEmpty()){

        Node *nodeNow = nodeList[0];
        nodeList.pop_front();
        int row = nodeNow->box->rowLoc;
        int col = nodeNow->box->colLoc;

        Node *nodeChild;
        if(row!=0){
            nodeChild = boxNode[row-1][col];
            if(nodeChild->box->currentWall==nullptr && nodeChild->finded==false){
                nodeChild->finded = true;
                nodeChild->parent = nodeNow;
                nodeChild->dist = nodeNow->dist+1;
                nodeList.push_back(nodeChild);
                if(nodeChild==boxNode[dest->rowLoc][dest->colLoc])break;
            }
        }
        if(row!=30){
            nodeChild = boxNode[row+1][col];
            if(nodeChild->box->currentWall==nullptr && nodeChild->finded==false){
                nodeChild->finded = true;
                nodeChild->parent = nodeNow;
                nodeChild->dist = nodeNow->dist+1;
                nodeList.push_back(nodeChild);
                if(nodeChild==boxNode[dest->rowLoc][dest->colLoc])break;
            }
        }
        if(col!=0){
            nodeChild = boxNode[row][col-1];
            if(nodeChild->box->currentWall==nullptr && nodeChild->finded==false){
                nodeChild->finded = true;
                nodeChild->parent = nodeNow;
                nodeChild->dist = nodeNow->dist+1;
                nodeList.push_back(nodeChild);
                if(nodeChild==boxNode[dest->rowLoc][dest->colLoc])break;
            }
        }
        if(col!=27){
            nodeChild = boxNode[row][col+1];
            if(nodeChild->box->currentWall==nullptr && nodeChild->finded==false){
                nodeChild->finded = true;
                nodeChild->parent = nodeNow;
                nodeChild->dist = nodeNow->dist+1;
                nodeList.push_back(nodeChild);
                if(nodeChild==boxNode[dest->rowLoc][dest->colLoc])break;
            }
        }

    }

    Node *currNode = boxNode[dest->rowLoc][dest->colLoc];
    while(true){
        if(currNode->parent->parent==nullptr)break;
        currNode = currNode->parent;
    }
    nextMove = currNode->box;

}




