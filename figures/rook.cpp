#include "rook.h"


Rook::Rook(QPoint coords, FigureColor figureColor):
    Figure(coords,figureColor)
{
    _figureType = FigureType::Rook;
}


QVariantList Rook::listPosibleTurns() const
{
    return squareCross();
}

QVariantList Rook::listPosibleCaptures() const
{
    QVariantList list;

    return list;
}
