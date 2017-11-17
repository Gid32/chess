#ifndef ROOK_H
#define ROOK_H

#include <QObject>
#include "figure.h"

class Rook : public Figure
{
    Q_OBJECT
public:
    Rook(QPoint coords, FigureColor figureColor);
    QVariantList listPosibleTurns() const;
};

#endif // ROOK_H
