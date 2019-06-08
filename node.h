#ifndef NODE_H
#define NODE_H

#include "box.h"

class Node
{
 public:
    Node();
    Node(Box *);

    bool finded;
    Node *parent;
    int dist;
    Box *box;
};

Node::Node(){
    box = nullptr;
    finded = false;
    parent = nullptr;
    dist = 10000;
}

Node::Node(Box *_box){
    box = _box;
    finded = false;
    parent = nullptr;
    dist = 10000;
}

#endif // NODE_H
