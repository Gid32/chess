#include "bishop.h"

Bishop::Bishop(QPoint coords, FigureColor figureColor):
    Figure(coords,figureColor)
{
    _figureType = FigureType::Bishop;
}

QVariantList Bishop::listPosibleTurns() const
{
    return diagonalCross();
}

QVariantList Bishop::listPosibleCaptures() const
{
    QVariantList list;

    return list;
}
