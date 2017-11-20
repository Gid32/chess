#ifndef QUEEN_H
#define QUEEN_H

#include <QObject>
#include "figure.h"

class Queen : public Figure
{
    Q_OBJECT
public:
    Queen(QPoint coords, FigureColor figureColor);
    QVariantList listPosibleTurns() const;
    QVariantList listPosibleCaptures() const;
};

#endif // QUEEN_H
