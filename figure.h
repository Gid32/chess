#ifndef Figure_H
#define Figure_H

#include <QObject>
#include <QPoint>
#include <QDebug>
#include <QList>

#include <QQmlEngine>
#include <QMap>
#include <QStringList>

const int BOARD_LENGTH = 8;

//Q_DECLARE_TYPE(Points);


class Figure : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPoint coords READ coords WRITE setCoords NOTIFY coordsChanged)
    Q_PROPERTY(int figureType READ figureType WRITE setFigureType NOTIFY figureTypeChanged)
    Q_PROPERTY(int figureColor READ figureColor NOTIFY figureColorChanged)
    Q_PROPERTY(QStringList getListCanTurn READ getListCanTurn CONSTANT)
    Q_PROPERTY(QVariantList listPosibleTurns READ listPosibleTurns CONSTANT)
    //Q_PROPERTY(Points getListCanTurn READ getListCanTurn)
   // Q_PROPERTY(QQmlListProperty<QList<QPoint>> getListCanTurn READ getListCanTurn )
    Q_ENUMS(FigureType)
    Q_ENUMS(FigureColor)
public:
    explicit Figure(QObject *parent = 0);
    enum FigureType {
        Pawn,
        Rook,
        Knight,
        Bishop,
        Queen,
        King,
    };
    enum FigureColor {
        White,
        Black,
    };
    Figure(QPoint coords, FigureType figureType, FigureColor figureColor);
    ~Figure();

    QPoint coords() const;
    void setCoords(QPoint coord);
    int figureType() const;
    int figureColor() const;
    void setFigureType(int figureType);

    QStringList getListCanTurn() const;
    QVariantList listPosibleTurns() const;

    Q_INVOKABLE void test();

signals:
    void coordsChanged(QPoint coord);
    void figureTypeChanged(int figureType);
    void figureColorChanged(int figureColor);
private:
    static bool _board[BOARD_LENGTH][BOARD_LENGTH];
    QPoint _coord;
    int _figureType;
    int _figureColor;


    //Points getListCanTurnPawn();
};

#endif // Figure_H
