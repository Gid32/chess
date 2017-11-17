#ifndef KING_H
#define KING_H

#include <QObject>
#include "figure.h"

class King : public Figure
{
    Q_OBJECT
public:
    King(QPoint coords, FigureColor figureColor);
    QVariantList listPosibleTurns() const;
};

#endif // KING_H
