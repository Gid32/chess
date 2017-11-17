#ifndef CHESSMODEL_H
#define CHESSMODEL_H

#include <QObject>
#include <QQmlListProperty>
#include <QMap>
#include <QPoint>

#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QDataStream>

class Figure;
class Pawn;
class Bishop;
class King;
class Knight;
class Queen;
class Rook;
#include "pawn.h"
#include "bishop.h"
#include "king.h"
#include "knight.h"
#include "queen.h"
#include "rook.h"

class ChessModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject* figure READ figure WRITE setFigure NOTIFY figureChanged)
    Q_PROPERTY(QQmlListProperty<Figure> data READ data NOTIFY dataChanged)
    Q_PROPERTY(QVariantList turns READ turns NOTIFY turnsChanged)
    Q_PROPERTY(Figure::FigureColor player READ player WRITE setPlayer NOTIFY playerChanged)
    Q_PROPERTY(QStringList log READ log NOTIFY logChanged)
    Q_CLASSINFO("DefaultProperty", "data")
public:
    ChessModel(QObject *parent = 0);
    QQmlListProperty<Figure> data();
    Q_INVOKABLE void add(Figure *figure);
    void clear();
    void flipBoard();
    Figure::FigureColor player();
    void setPlayer(Figure::FigureColor player);
    QObject* figure();
    void setFigure(QObject *figure);
    QVariantList turns();
    QStringList log();

    Q_INVOKABLE Figure *getFigureFromPoint(QPoint coord);
    Q_INVOKABLE void saveLog();
    Q_INVOKABLE void loadLog();
signals:
    void dataChanged();
    void playerChanged(Figure::FigureColor player);
    void figureChanged(QObject *figure);
    void turnsChanged(QVariantList turns);
    void logChanged(QStringList log);
    void started();
public slots:
    void figureTurn(Figure *figure, QPoint point);
    void start();
private:
    static void appendData(QQmlListProperty<Figure> *list, Figure *value);
    static int countData(QQmlListProperty<Figure> *list);
    static Figure *atData(QQmlListProperty<Figure> *list, int index);
    static void clearData(QQmlListProperty<Figure> *list);
    void logAdd(QPoint from, QPoint to);

    QList<Figure*> m_data;
    Figure::FigureColor _player;
    Figure *_figure;
    QList<QPoint> _history;
};


#endif
