#ifndef MOVABLEITEM_H
#define MOVABLEITEM_H

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <time.h>

class Node;
class Box;
class MovableItem : public QGraphicsPixmapItem
{
public:
    MovableItem();
    virtual ~MovableItem();

    //polymorphism
    virtual void setImage() = 0;
    virtual void move() = 0;

    //moving direction
    void changeDir(int dir);
    int getDir();
    int lastMoveDir;

    //get position
    int getRow();
    int getCol();
    Box *currentBox;

    //move algorithm
    void nodeInitialize();
    void searchNext(Box *dest);

    //for ghostObstacle
    void addDest(Box *box);



protected:
    QString name;
    int moveDir; //0freeze 1up 2down 3left 4right
    Box *nextMove; //the next position searched by searchNext()
    Node *boxNode[31][28]; //nodes used for BFS
    QList<Box*> obstacleChoice; //moving choices for GhostObstacle


};

#endif // MOVABLEITEM_H
