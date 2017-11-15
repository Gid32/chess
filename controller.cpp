#include "controller.h"

Controller::Controller(QQmlContext *context)
{
    _model = new ChessModel();

    context->setContextProperty("chessModel", _model);
    qmlRegisterType<Figure>("cpp", 1, 0, "Figure");
    //qRegisterMetaType<Points>();
    //qmlRegisterType<Points>("cpp", 1, 0, "listPoint");
}


void Controller::startGame()
{
    qDebug()<<"nahuy";
    placeFigures();
    emit loadPlayedGameWindow();
}

void Controller::leaveGame()
{
    qDebug()<<"leave";
    _model->clear();
    emit loadDefaultWindow();
}

void Controller::placeFiguresPair(Figure::FigureType figureType, int Column)
{
    int Row = 0;
    if(figureType == Figure::FigureType::Pawn)
        Row = 1;
    _model->add(new Figure(QPoint(Column,(BOARD_LENGTH-1)-Row), figureType, Figure::FigureColor::White));
    _model->add(new Figure(QPoint(Column,Row), figureType, Figure::FigureColor::Black));
}

void Controller::placeFigures()
{
    for(int i = 0;i<BOARD_LENGTH;i++)
    {
        placeFiguresPair(Figure::FigureType::Pawn, i);
    }

    placeFiguresPair(Figure::FigureType::Rook, 0);
    placeFiguresPair(Figure::FigureType::Knight, 1);
    placeFiguresPair(Figure::FigureType::Bishop, 2);
    placeFiguresPair(Figure::FigureType::Queen, 3);
    placeFiguresPair(Figure::FigureType::King, 4);
    placeFiguresPair(Figure::FigureType::Bishop, 5);
    placeFiguresPair(Figure::FigureType::Knight, 6);
    placeFiguresPair(Figure::FigureType::Rook, 7);

    emit loadPlayedGameWindow();
}

void Controller::initConnection(QObject *qml)
{
    _qml = qml;
    connect(_qml,SIGNAL(startGame()),
            this,SLOT(startGame()));

    connect(this,SIGNAL(loadPlayedGameWindow()),
            _qml,SLOT(loadPlayedGameWindow()));

    connect(_qml,SIGNAL(leaveGame()),
            this,SLOT(leaveGame()));

    connect(this,SIGNAL(loadDefaultWindow()),
            _qml,SLOT(loadDefaultWindow()));
}

