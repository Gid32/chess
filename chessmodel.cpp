#include "chessmodel.h"
#include "figure.h"

ChessModel::ChessModel(QObject *parent):
    QObject(parent)
{
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



