#include "figure.h"

Figure::FigureColor Figure::_board[BOARD_LENGTH][BOARD_LENGTH] = { Figure::FigureColor::NoColor};

Figure::Figure(QObject *parent) :
    QObject(parent)
{
}

Figure::Figure(QPoint coords, FigureColor figureColor, QObject *parent) :
        QObject(parent)
{
    _figureColor = figureColor;
    _coord = coords;
    _board[_coord.x()][_coord.y()] = figureColor;
    //qDebug()<<_coord.x()<<_coord.y()<<figureColor;
    _countTurns = 0;
}

Figure::~Figure()
{
   _board[_coord.x()][_coord.y()] = NoColor;
}

QPoint Figure::coords() const
{
    return _coord;
}

void Figure::moveToCoords(QPoint coord)
{
    if(coord == _coord)
        return;

    _board[_coord.x()][_coord.y()] = FigureColor::NoColor;

    _coord = coord;

    _board[_coord.x()][_coord.y()] = (FigureColor)_figureColor;
    emit coordsChanged(_coord);
    emit listPosibleTurnsChanged(QVariantList());
}

QVariantList Figure::squareCross() const
{
    QVariantList list;

    list.append(line(1, 0, BOARD_LENGTH));
    list.append(line(-1, 0, BOARD_LENGTH));
    list.append(line(0, 1, BOARD_LENGTH));
    list.append(line(0, -1, BOARD_LENGTH));

    return list;
}

QVariantList Figure::diagonalCross() const
{
    QVariantList list;

    list.append(line(1, 1, BOARD_LENGTH));
    list.append(line(1, -1, BOARD_LENGTH));
    list.append(line(-1, 1, BOARD_LENGTH));
    list.append(line(-1, -1, BOARD_LENGTH));

    return list;
}

QVariantList Figure::line(int dX, int dY, int maxSteps) const
{
    QVariantList list;
    int currentStep = 1;

    while (currentStep <= maxSteps)
    {
        QPoint point(_coord + QPoint(dX * currentStep,dY * currentStep));
        if(!checkCoordLegal(point))break;
        if(getBoardValue(point) == _figureColor)break;
        if(getBoardValue(point) == -_figureColor)
        {
            list.append(point);
            break;
        }
        else
        {
            list.append(point);
        }
        currentStep++;
    }

    return list;
}

int Figure::figureType() const
{
    return _figureType;
}

int Figure::figureColor() const
{
    return _figureColor;
}

void Figure::setFigureType(int figureType)
{
    if(figureType == _figureType)
        return;
    _figureType = figureType;
    emit figureTypeChanged(_figureType);
}

void Figure::turn(QPoint point)
{
    _countTurns++;
    emit wantTurn(this,point);
}

QVariantList Figure::listPosibleTurns() const
{
    return QVariantList();
}

QVariantList Figure::listPosibleCaptures() const
{
    return QVariantList();
}

Figure::FigureColor Figure::getBoardValue(QPoint coord)
{
    return _board[coord.x()][coord.y()];
}


bool Figure::checkCoordLegal(QPoint coord)
{
    if(coord.y() < BOARD_LENGTH && coord.y() >= 0 && coord.x() < BOARD_LENGTH && coord.x() >= 0)
        return true;
    return false;
}

void Figure::debugBoard()
{

    for(int i=0;i<BOARD_LENGTH;i++)
    {
        QString str = "";
        for(int j=0;j<BOARD_LENGTH;j++)
            str+=QString::number(_board[j][i])+" ";
        qDebug()<<str;
    }
}

void Figure::clearBoard()
{
    for(int i=0;i<BOARD_LENGTH;i++)
        for(int j=0;j<BOARD_LENGTH;j++)
            _board[i][j] = NoColor;
}




