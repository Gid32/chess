#include "figure.h"

//Points::Points(QObject *parent) :
//    QObject(parent)
//{

//}

//Points::Points(const Points&)
//{

//}

//Points &Points::operator =(const Points&)
//{


//}


bool Figure::_board[BOARD_LENGTH][BOARD_LENGTH] = {};

Figure::Figure(QObject *parent) :
    QObject(parent)
{
}

Figure::~Figure()
{
   _board[_coord.x()][_coord.y()] = false;
}

Figure::Figure(QPoint coords, FigureType figureType)
{
    _coord = coords;
    _figureType = figureType;
    qDebug()<<_coord.x()<<_coord.y()<<_board[_coord.x()][_coord.y()];
    _board[_coord.x()][_coord.y()] = true;
    qDebug()<<_coord.x()<<_coord.y()<<_board[_coord.x()][_coord.y()];
}

QPoint Figure::coords() const
{
    return _coord;
}

void Figure::setCoords(QPoint coord)
{
    if(coord == _coord)
        return;
    _board[_coord.x()][_coord.y()] = false;
    _coord = coord;
    _board[_coord.x()][_coord.y()] = true;
    emit coordsChanged(_coord);
}

int Figure::figureType() const
{
    return _figureType;
}

void Figure::setFigureType(int figureType)
{
    if(figureType == _figureType)
        return;
    _figureType = figureType;
    emit figureTypeChanged(_figureType);
}

//Points Figure::getListCanTurn()
//{
//    switch(_figureType)
//    {
//        case WhitePawn:
//        case BlackPawn:
//            return getListCanTurnPawn();
//    default:
//        return getListCanTurnPawn();
//    }
//}

//Points Figure::getListCanTurnPawn()
//{
//    POINTS list;
//    int startY = _coord.x();

//    for(int i=startY;i<startY+1;i++)
//    {
//        if(i >= BOARD_LENGTH || i < 0)
//            continue;
//        if(!_board[_coord.x()][i])
//            list.append(QPoint(_coord.x(),i));
//    }
//    qDebug()<<"aaa";
//    return Points();
//}

QStringList Figure::getListCanTurn() const
{
    return QStringList() << "orange" << "skyblue";
}

QVariantList Figure::listPosibleTurns() const
{
    QVariantList list;
    int startY = _coord.y()+1;
    if(startY < BOARD_LENGTH && startY >= 0)
        list.append(QVariant::fromValue(QPoint(_coord.x(),startY)));
//    for(int i=startY;i<startY+1;i++)
//    {
//        if(i >= BOARD_LENGTH || i < 0)
//            continue;
//        qDebug()<<"add"<<_coord.x()<<i;
//        if(!_board[_coord.x()][i])
//            list.append(QVariant::fromValue(QPoint(_coord.x(),i)));
//    }
    //qDebug()<<"aaa";
    return list;
}

void Figure::test()
{
    qDebug()<<"aaaa";
}




