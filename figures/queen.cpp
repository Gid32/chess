#include "queen.h"


Queen::Queen(QPoint coords, FigureColor figureColor):
    Figure(coords,figureColor)
{
    _figureType = FigureType::Queen;
}


QVariantList Queen::listPosibleTurns() const
{
    QVariantList list;
    list.append(squareCross());
    list.append(diagonalCross());
    return list;
}

QVariantList Queen::listPosibleCaptures() const
{
    QVariantList list;

    return list;
}
