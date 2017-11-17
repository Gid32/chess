#ifndef KNIGHT_H
#define KNIGHT_H

#include <QObject>
#include "figure.h"

class Knight : public Figure
{
    Q_OBJECT
public:
    Knight(QPoint coords, FigureColor figureColor);
    QVariantList listPosibleTurns() const;
};

#endif // KNIGHT_H
