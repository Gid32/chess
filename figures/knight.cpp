#include "knight.h"


Knight::Knight(QPoint coords, FigureColor figureColor):
    Figure(coords,figureColor)
{
    _figureType = FigureType::Knight;
}



QVariantList Knight::listPosibleTurns() const
{
    QVariantList list;

    list.append(line(1, 2, 1));
    list.append(line(1, -2, 1));
    list.append(line(-1, 2, 1));
    list.append(line(-1, -2, 1));
    list.append(line(2, 1, 1));
    list.append(line(2, -1, 1));
    list.append(line(-2, 1, 1));
    list.append(line(-2, -1, 1));

    return list;
}

QVariantList Knight::listPosibleCaptures() const
{
    QVariantList list;

    return list;
}
