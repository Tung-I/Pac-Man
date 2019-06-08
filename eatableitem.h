#ifndef EATABLEITEM_H
#define EATABLEITEM_H

#include <QGraphicsEllipseItem>
#include <QBrush>

class EatableItem : public QGraphicsEllipseItem
{
public:
    EatableItem(bool pellet);
    void setPellet(bool val);
    bool getPellet(); //return is power pellet or not
    void change2Pellet(); //change into power pellet

    int row;
    int col;

private:
    QBrush brush;
    QColor itemColor;
    bool powerPellet; //is power pellet or not
};

#endif // EATABLEITEM_H
