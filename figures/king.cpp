#include "king.h"

King::King(QPoint coords, FigureColor figureColor):
    Figure(coords,figureColor)
{
    _figureType = FigureType::King;
}


QVariantList King::listPosibleTurns() const
{
    QVariantList list;
    list.append(line(1, 0, 1));
    list.append(line(-1, 0, 1));
    list.append(line(0, 1, 1));
    list.append(line(0, -1, 1));
    list.append(line(1, 1, 1));
    list.append(line(-1, -1, 1));
    list.append(line(-1, 1, 1));
    list.append(line(1, -1, 1));
    return list;
}

QVariantList King::listPosibleCaptures() const
{
    QVariantList list;

    return list;
}
