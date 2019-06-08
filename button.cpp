#include "button.h"

#include <QGraphicsTextItem>
#include <QBrush>


Button::Button(QString name, QColor color, QColor hoverColor, QGraphicsItem *parent) : QGraphicsRectItem(parent)
{

    //set size and color
    setRect(0,0,200,50);
    setButtonColor(color, hoverColor);


    //draw Text
    text = new QGraphicsTextItem(name, this);
    int xPos = int(rect().width()/2 - text->boundingRect().width()/2);
    int yPos = int(rect().height()/2 - text->boundingRect().height()/2);
    text->setPos(xPos,yPos);
    textColor = QColor(0, 0, 0, 255);
    this->setTextColor(textColor);

    //Allow responding to hover
    setAcceptHoverEvents(true);

}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event) emit clicked();
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    //change color
    if(event){
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(buttonHoverColor);
    setBrush(brush);
    }
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    //change color
    if(event){
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(buttonColor);
    setBrush(brush);
    }
}

void Button::setTextColor(QColor color){
    textColor = color;
    text->setDefaultTextColor(textColor);
}

void Button::setButtonColor(QColor color, QColor hoverColor){
    buttonColor = color;
    buttonHoverColor = hoverColor;

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    setBrush(brush);
}
