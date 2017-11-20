#include "chessmodel.h"
#include "figure.h"

ChessModel::ChessModel(QObject *parent):
    QObject(parent)
{
    _figure = nullptr;
    _player = Figure::White;
}

QQmlListProperty<Figure> ChessModel::data()
{
    return QQmlListProperty<Figure>(static_cast<QObject *>(this), static_cast<void *>(&m_data),
                                     &ChessModel::appendData, &ChessModel::countData,
                                     &ChessModel::atData, &ChessModel::clearData);
}

void ChessModel::add(Figure *figure)
{
    m_data.append(figure);
    connect(figure,SIGNAL(wantTurn(Figure*,QPoint)),
            this,SLOT(figureTurn(Figure*,QPoint)));
    emit dataChanged();
}

void ChessModel::clear()
{
    QList<Figure*> test;
    for(int i=0;i<m_data.size();i++)
        test.append(m_data.at(i));
    m_data.clear();
    emit dataChanged();

    qDeleteAll(test);
    setPlayer(Figure::White);
    setActiveFigure(nullptr);
    Figure::clearBoard();
    _history.clear();
    emit logChanged(log());
}

void ChessModel::appendData(QQmlListProperty<Figure> *list, Figure *value)
{
    QList<Figure*> *data = static_cast<QList<Figure*> *>(list->data);
    data->append(value);
}

int ChessModel::countData(QQmlListProperty<Figure> *list)
{
    QList<Figure*> *data = static_cast<QList<Figure*> *>(list->data);
    return data->size();
}

Figure *ChessModel::atData(QQmlListProperty<Figure> *list, int index)
{
    QList<Figure*> *data = static_cast<QList<Figure*> *>(list->data);
    return data->at(index);
}

void ChessModel::clearData(QQmlListProperty<Figure> *list)
{
    QList<Figure*> *data = static_cast<QList<Figure*> *>(list->data);
    qDeleteAll(data->begin(), data->end());
    data->clear();
}

Figure::FigureColor ChessModel::player()
{
    return _player;
}

void ChessModel::setPlayer(Figure::FigureColor player)
{
    if(player == _player)
        return;
    _player = player;
    emit playerChanged(_player);
}

QObject* ChessModel::figure()
{
    return _figure;
}

void ChessModel::setActiveFigure(QObject *figure)
{
    if(_figure == figure)
        return;
    //Figure::debugBoard();
    _figure = qobject_cast<Figure*>(figure);
    emit figureChanged(_figure);
    emit turnsChanged(turns());
}

Figure *ChessModel::getFigureFromPoint(QPoint coord)
{
    int index = getFigureIndexFromPoint(coord);
    if (index >= 0) return m_data.at(index);
    else return nullptr;
}

QVariantList ChessModel::turns()
{
    if(_figure)
        return _figure->listPosibleTurns();
    return QVariantList();
}

void ChessModel::start()
{
    clear();
    //Figure::debugBoard();

    int row,rowPawn;
    for(int i = -1;i<2;i+=2)
    {
        Figure::FigureColor color = (Figure::FigureColor)i;
        row = i==1 ? 0 : (BOARD_LENGTH-1);
        rowPawn = i==1 ? row+1 : row-1;
        for(int j = 0;j<BOARD_LENGTH;j++)
            add(new Pawn(QPoint(j,rowPawn), color));

        add(new Rook(QPoint(0,row), color));
        add(new Knight(QPoint(1,row), color));
        add(new Bishop(QPoint(2,row), color));
        add(new Queen(QPoint(3,row), color));
        add(new King(QPoint(4,row), color));
        add(new Bishop(QPoint(5,row), color));
        add(new Knight(QPoint(6,row), color));
        add(new Rook(QPoint(7,row), color));
    }

    emit started();
}

QStringList ChessModel::log()
{
    QStringList list;
    for(int i=0;i<_history.size();i+=2)
    {
        list.append(QString::number(_history.at(i).x())+QString::number(_history.at(i).y())+" -> "+
                    QString::number(_history.at(i+1).x())+QString::number(_history.at(i+1).y()));
    }
    return list;
}




void ChessModel::captureTryAt(QPoint point)
{
    int target = getFigureIndexFromPoint(point);
    if (target > -1)
    {
        m_data.removeAt(target);
        emit dataChanged();
    }
}

void ChessModel::figureTurn(Figure *figure, QPoint point)
{
    logAdd(figure->coords(),point);

    if(Figure::getBoardValue(point) == -figure->figureColor())
        captureTryAt(point);

    figure->moveToCoords(point);

    if(_player == Figure::Black)
        setPlayer(Figure::White);
    else
        setPlayer(Figure::Black);

    setActiveFigure(nullptr);
}

void ChessModel::logAdd(QPoint from, QPoint to)
{
    _history.append(from);
    _history.append(to);
    emit logChanged(log());
}

int ChessModel::getFigureIndexFromPoint(QPoint coord)
{
    for(int i=0;i<m_data.size();i++)
        if(m_data.at(i)->coords() == coord)
            return i;
    return -1;
}

void ChessModel::saveLog()
{
    static const char* const FILE_NAME = "test.txt";
    QFile out(FILE_NAME);
    if(out.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&out);
        for(int i=0;i<_history.size();i+=2)
            stream << _history.at(i).x()   <<" "<< _history.at(i).y()<<" "
                   << _history.at(i+1).x() <<" "<< _history.at(i+1).y()<<"\r\n";
        out.close();
    }
}

void ChessModel::loadLog()
{
    static const char* const FILE_NAME = "test.txt";
    QFile in(FILE_NAME);
    QList<QPoint> history;
    if(in.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&in);
        int x, y, x2, y2;
        while(!stream.atEnd())
        {
            stream>>x;
            stream>>y;
            stream>>x2;
            stream>>y2;
            if(x == 0 && y == 0 && y2 == 0 && x2 == 0)
                break;
            history.append(QPoint(x,y));
            history.append(QPoint(x2,y2));
        }
        in.close();
    }

    start();

    /*for(int i=0;i<history.size();i+=2)
        figureTurn(getFigureFromPoint(history.at(i)),history.at(i+1));
    */
}



