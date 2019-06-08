#ifndef BUTTON_H
#define BUTTON_H


#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>

class Button:public QObject, public QGraphicsRectItem
{
     Q_OBJECT
public:

    Button(QString name, QColor color = QColor(255, 209, 5, 255), QColor hoverColor = QColor(219, 179, 0, 255),
           QGraphicsItem * parent = nullptr);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    void setTextColor(QColor _color);
    void setButtonColor(QColor _color, QColor _hoverColor);

signals:
    void clicked();

private:
    QGraphicsTextItem *text;
    QColor buttonColor;
    QColor buttonHoverColor;
    QColor textColor;
};

#endif // BUTTON_H
