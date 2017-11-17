#include "rook.h"


Rook::Rook(QPoint coords, FigureColor figureColor):
    Figure(coords,figureColor)
{
    _figureType = FigureType::Rook;
}


QVariantList Rook::listPosibleTurns() const
{
    QVariantList list;
    int startY = _coord.y()-2;
    if(startY < BOARD_LENGTH && startY >= 0)
        list.append(QVariant::fromValue(QPoint(_coord.x(),startY)));
    return list;
}