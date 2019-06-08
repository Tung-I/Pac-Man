#include "wall.h"

Wall::Wall(int w, int l)
{
    //set size and color
    setRect(0,0,w*25-14,l*25-14);

    wallColor = QColor(10, 10, 10, 255);
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(wallColor);
    setBrush(brush);

    pen.setWidth(7);
    pen.setColor(QColor(0, 0, 199, 255));
    setPen(pen);

    setZValue(2);

}
