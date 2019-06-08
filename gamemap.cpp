#include "gamemap.h"
#include "game.h"
#include <QDebug>

extern Game *game;

GameMap::GameMap()
{
    drawBox(700-25*14, 80);
    drawAllWall();
    drawDot();

    drawPac(23, 13);
    drawGhost1(14, 12);
    drawGhost2(14, 13);
    drawGhost3(14, 14);
    drawGhost4(14, 15);

}

void GameMap::drawBox(int x, int y){
    int SHIFT = 25;
    for(int i = 0; i < 31; i++) {
        for(int j = 0; j < 28; j++){
            Box *box = new Box();
            this->boxes[i][j] = box;
            box->rowLoc = i;
            box->colLoc = j;
            box->setPos(x+SHIFT*j,y+SHIFT*i);
            game->addToScene(box);
        }
    }
}

void GameMap::drawWall(int x_l, int x_r, int y_u, int y_d){
    Wall *_wall = new Wall(x_r-x_l+1, y_d-y_u+1);
    _wall->setPos(boxes[y_u][x_l]->x()+7, boxes[y_u][x_l]->y()+7);
    for(int i=x_l;i<=x_r;++i){
        for(int j=y_u;j<=y_d;++j){
            boxes[j][i]->currentWall = _wall;
        }
    }
    game->addToScene(_wall);
}

void GameMap::drawDot(){
    dotLeft = 240;
    for(int i=0;i<28;++i){
        for(int j=0;j<9;++j){
            if(boxes[j][i]->currentWall!=nullptr)continue;
            EatableItem *temp = new EatableItem(false);
            dotList.append(temp);
            game->addToScene(temp);
            temp->setPos(boxes[j][i]->x()+9, boxes[j][i]->y()+9);
            boxes[j][i]->currentDot = temp;
            temp->row = j;
            temp->col = i;
        }
    }
    for(int i=0;i<28;++i){
        for(int j=20;j<31;++j){
            if(boxes[j][i]->currentWall!=nullptr)continue;
            if(j==23&&i==13)continue;
            if(j==23&&i==14)continue;
            EatableItem *temp = new EatableItem(false);
            dotList.append(temp);
            game->addToScene(temp);
            temp->setPos(boxes[j][i]->x()+9, boxes[j][i]->y()+9);
            boxes[j][i]->currentDot = temp;
            temp->row = j;
            temp->col = i;
        }
    }
    for(int i=9;i<20;++i){
        EatableItem *temp1 = new EatableItem(false);
        EatableItem *temp2 = new EatableItem(false);
        dotList.append(temp1);
        dotList.append(temp2);
        game->addToScene(temp1);
        game->addToScene(temp2);
        temp1->setPos(boxes[i][6]->x()+9, boxes[i][6]->y()+9);
        temp2->setPos(boxes[i][21]->x()+9, boxes[i][21]->y()+9);
        boxes[i][6]->currentDot = temp1;
        boxes[i][21]->currentDot = temp2;
        temp1->row = i;
        temp1->col = 6;
        temp2->row = i;
        temp2->col = 21;
    }
    boxes[3][1]->currentDot->change2Pellet();
    boxes[3][1]->currentDot->setPos(boxes[3][1]->currentDot->x()-4, boxes[3][1]->currentDot->y()-4);
    boxes[3][26]->currentDot->change2Pellet();
    boxes[3][26]->currentDot->setPos(boxes[3][26]->currentDot->x()-4, boxes[3][26]->currentDot->y()-4);
    boxes[23][1]->currentDot->change2Pellet();
    boxes[23][1]->currentDot->setPos(boxes[23][1]->currentDot->x()-4, boxes[23][1]->currentDot->y()-4);
    boxes[23][26]->currentDot->change2Pellet();
    boxes[23][26]->currentDot->setPos(boxes[23][26]->currentDot->x()-4, boxes[23][26]->currentDot->y()-4);
}

void GameMap::drawPac(int rol, int col){
    pacman = new Pacman();
    boxes[rol][col]->pacPlaceIn(pacman);
    game->addToScene(pacman);
}

void GameMap::drawGhost1(int rol, int col){
    ghost1 = new GhostChase();
    boxes[rol][col]->ghost1PlaceIn(ghost1);
    game->addToScene(ghost1);
}
void GameMap::drawGhost2(int rol , int col){
    ghost2 = new GhostAmbush1();
    boxes[rol][col]->ghost2PlaceIn(ghost2);
    game->addToScene(ghost2);
}
void GameMap::drawGhost3(int rol , int col){
    ghost3 = new GhostAmbush2();
    boxes[rol][col]->ghost3PlaceIn(ghost3);
    game->addToScene(ghost3);
}
void GameMap::drawGhost4(int rol , int col){
    ghost4 = new GhostObstacle();
    boxes[rol][col]->ghost4PlaceIn(ghost4);
    game->addToScene(ghost4);

    ghost4->addDest(boxes[5][6]);
    ghost4->addDest(boxes[5][21]);
    ghost4->addDest(boxes[20][6]);
    ghost4->addDest(boxes[20][21]);
    ghost4->addDest(boxes[1][1]);
    ghost4->addDest(boxes[1][26]);
    ghost4->addDest(boxes[29][1]);
    ghost4->addDest(boxes[29][26]);
    ghost4->addDest(boxes[17][13]);
    ghost4->addDest(boxes[11][13]);
    ghost4->addDest(boxes[5][13]);
}


void GameMap::reset(){
    //replace dots
    int n = dotList.size();
    for(int i=0;i<n;++i){
        dotList[i]->setVisible(true);
        boxes[dotList[i]->row][dotList[i]->col]->currentDot = dotList[i];
    }
    dotLeft = 240;
    //reset pacman
    boxes[pacman->getRow()][pacman->getCol()]->currentPac = nullptr;
    boxes[23][13]->pacPlaceIn(pacman);
    pacman->lastMoveDir = 4;
    pacman->setPixmap(QPixmap(":/new/prefix1/imgs/pacman_right.png"));
    //reset ghost
    resetGhost1();
    resetGhost2();
    resetGhost3();
    resetGhost4();
}

void GameMap::resetGhost1(){
    boxes[ghost1->getRow()][ghost1->getCol()]->currentGhost1 = nullptr;
    boxes[14][12]->ghost1PlaceIn(ghost1);
}
void GameMap::resetGhost2(){
    boxes[ghost2->getRow()][ghost2->getCol()]->currentGhost2 = nullptr;
    boxes[14][13]->ghost2PlaceIn(ghost2);
}
void GameMap::resetGhost3(){
    boxes[ghost3->getRow()][ghost3->getCol()]->currentGhost3 = nullptr;
    boxes[14][14]->ghost3PlaceIn(ghost3);
}
void GameMap::resetGhost4(){
    boxes[ghost4->getRow()][ghost4->getCol()]->currentGhost4 = nullptr;
    boxes[14][15]->ghost4PlaceIn(ghost4);
}


int GameMap::getDotLeft(){return dotLeft;}
void GameMap::reduceDotLeft(){dotLeft--;}

void GameMap::drawAllWall(){
    drawWall(0, 27, 0, 0);
    drawWall(0, 27, 30, 30);

    drawWall(13, 14, 0, 4);
    drawWall(0, 2, 24, 25);
    drawWall(27-2, 27-0, 24, 25);

    drawWall(13-3, 14+3, 6, 7);
    drawWall(13-3, 14+3, 18, 19);
    drawWall(13, 14, 6, 10);
    drawWall(13, 14, 18, 22);

    drawWall(7, 8, 6, 13);
    drawWall(7, 11, 9, 10);
    drawWall(27-8, 27-7, 6, 13);
    drawWall(27-11, 27-7, 9, 10);

    drawWall(7, 8, 15, 19);
    drawWall(27-8, 27-7, 15, 19);

    //ghost house
    drawWall(13-3, 14+3, 15, 15);
    drawWall(13-3, 13-3, 12, 15);
    drawWall(14+3, 14+3, 12, 15);
    drawWall(10, 12, 12, 12);
    drawWall(15, 17, 12, 12);

    drawWall(7, 11, 21, 22);
    drawWall(27-11, 27-7, 21, 22);
    drawWall(2, 5, 21, 22);
    drawWall(4, 5, 21, 25);
    drawWall(22, 25, 21, 22);
    drawWall(22, 23, 21, 25);

    drawWall(13-3, 14+3, 24, 25);
    drawWall(13, 14, 24, 28);

    drawWall(2, 11, 27, 28);
    drawWall(7, 8, 24, 28);
    drawWall(27-11, 27-2, 27, 28);
    drawWall(19, 20, 24, 28);

    drawWall(0, 0, 0, 9);
    drawWall(27, 27, 0, 9);
    drawWall(0, 0, 19, 30);
    drawWall(27, 27, 19, 30);

    drawWall(0, 5, 9, 9);
    drawWall(0, 5, 19, 19);
    drawWall(27-5, 27-0, 9, 9);
    drawWall(27-5, 27-0, 19, 19);

    drawWall(5, 5, 9, 13);
    drawWall(5, 5, 15, 19);
    drawWall(27-5, 27-5, 9, 13);
    drawWall(27-5, 27-5, 15, 19);

    drawWall(0, 5, 13, 13);
    drawWall(0, 5, 15, 15);
    drawWall(27-5, 27-0, 13, 13);
    drawWall(27-5, 27-0, 15, 15);

    drawWall(2, 5, 2, 4);
    drawWall(27-5, 27-2, 2, 4);

    drawWall(2, 5, 6, 7);
    drawWall(27-5, 27-2, 6, 7);

    drawWall(7, 11, 2, 4);
    drawWall(27-11, 27-7, 2, 4);
}
