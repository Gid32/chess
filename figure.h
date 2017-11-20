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


class Figure : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPoint coords READ coords WRITE moveToCoords NOTIFY coordsChanged)
    Q_PROPERTY(int figureType READ figureType WRITE setFigureType NOTIFY figureTypeChanged)
    Q_PROPERTY(int figureColor READ figureColor NOTIFY figureColorChanged)

    Q_PROPERTY(QVariantList listPosibleTurns READ listPosibleTurns NOTIFY  listPosibleTurnsChanged)
    Q_PROPERTY(QVariantList listPosibleCaptures READ listPosibleCaptures NOTIFY listPosibleCapturesChanged)

    Q_PROPERTY(QPoint turn WRITE turn)
    Q_ENUMS(FigureType)
    Q_ENUMS(FigureColor)
    void addLinearAjastedPoint(QVariantList list, QPoint point) const;

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
        White = -1,
        Black = 1,
        NoColor = 0,
    };
    Figure(QPoint coords, FigureColor figureColor, QObject *parent = 0);
    ~Figure();

    QPoint coords() const;
    void moveToCoords(QPoint coord);
    int figureType() const;
    int figureColor() const;
    void setFigureType(int figureType);
    void turn(QPoint point);

    virtual QVariantList listPosibleTurns() const ;
    virtual QVariantList listPosibleCaptures() const ;

    static FigureColor getBoardValue(QPoint coord);

    static bool checkCoordLegal(QPoint coord);
    static void debugBoard();
    static void clearBoard();
signals:
    void coordsChanged(QPoint coord);

    void figureTypeChanged(int figureType);
    void figureColorChanged(int figureColor);
    void listPosibleTurnsChanged(QVariantList listPosibleTurns);
    void listPosibleCapturesChanged(QVariantList listPosibleCaptures);
    void wantTurn(Figure*,QPoint);
protected:
    static FigureColor _board[BOARD_LENGTH][BOARD_LENGTH];
    QPoint _coord;
    int _figureType;
    int _figureColor;
    int _countTurns;

    QVariantList squareCross() const;
    QVariantList diagonalCross() const;
    QVariantList line(int dX, int dY, int maxSteps) const;

};

#endif // Figure_H
