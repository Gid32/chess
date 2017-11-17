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
    qDebug()<<_coord.x()<<_coord.y()<<figureColor;
    _countTurns = 0;
}

Figure::~Figure()
{
   _board[_coord.x()][_coord.y()] = NoColor;
}

//Figure::Figure(QPoint coords, FigureType figureType, FigureColor figureColor)
//{
//    _coord = coords;
//    _figureType = figureType;
//    _figureColor = figureColor;
//    _board[_coord.x()][_coord.y()] = true;
//}

QPoint Figure::coords() const
{
    return _coord;
}

void Figure::setCoords(QPoint coord)
{
    if(coord == _coord)
        return;
    _coord = coord;
    _board[coord.x()][coord.y()] = (FigureColor)_figureColor;
    emit coordsChanged(_coord);
    emit listPosibleTurnsChanged(QVariantList());
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




