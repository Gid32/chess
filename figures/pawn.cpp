#include "pawn.h"

Pawn::Pawn(QPoint coords, FigureColor figureColor):
    Figure(coords,figureColor)
{
    _figureType = FigureType::Pawn;
}

QVariantList Pawn::listPosibleTurns() const
{

    QVariantList list;

    int startY = _coord.y()+_figureColor;
    QPoint point(_coord.x(),startY);

    //step up
    if(checkCoordLegal(point) && getBoardValue(point) == NoColor)
        list.append(QVariant::fromValue(point));

    //step up up
    if(_countTurns == 0)
    {
        QPoint point2(_coord.x(),startY+_figureColor);
        if(checkCoordLegal(point2) && getBoardValue(point2) == NoColor)
            list.append(QVariant::fromValue(point2));
    }

    list.append(listPosibleCaptures());

    return list;
}

QVariantList Pawn::listPosibleCaptures() const
{
    QVariantList list;

    //kill left
    QPoint point3(_coord.x()-1,_coord.y()+_figureColor);
        if(checkCoordLegal(point3))
        {
            if(getBoardValue(point3) != _figureColor && getBoardValue(point3) != NoColor)
                list.append(QVariant::fromValue(point3));
        }

    //kill right
    QPoint point4(_coord.x()+1,_coord.y()+_figureColor);
        if(checkCoordLegal(point4))
        {
            if(getBoardValue(point4) != _figureColor && getBoardValue(point4) != NoColor)
                list.append(QVariant::fromValue(point4));
        }

    return list;
}
