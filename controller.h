#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QDebug>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "chessmodel.h"
#include "figure.h"
#include "pawn.h"
#include "bishop.h"
#include "king.h"
#include "knight.h"
#include "queen.h"
#include "rook.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    Controller(QQmlContext *context);
    void initConnection(QObject *qml);
signals:
    void loadPlayedGameWindow();
    void loadDefaultWindow();
public slots:
    void startGame();
    void leaveGame();
private:
    ChessModel *_model;
    QObject *_qml;
};

#endif // CONTROLLER_H
