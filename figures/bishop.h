#ifndef BISHOP_H
#define BISHOP_H

#include <QObject>
#include "figure.h"

class Bishop : public Figure
{
    Q_OBJECT
public:
    Bishop(QPoint coords, FigureColor figureColor);
    QVariantList listPosibleTurns() const;
    QVariantList listPosibleCaptures() const;
};

#endif // BISHOP_H
