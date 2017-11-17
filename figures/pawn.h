#ifndef PAWN_H
#define PAWN_H

#include <QObject>
#include "figure.h"

class Pawn : public Figure
{
    Q_OBJECT
public:
    Pawn(QPoint coords, FigureColor figureColor);
    QVariantList listPosibleTurns() const;
};

#endif // PAWN_H
