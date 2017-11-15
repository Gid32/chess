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
    int whitePos = 6, blackPos = 1;
    for(int i = 0;i<BOARD_LENGTH;i++)
    {
        Figure *figure = new Figure(QPoint(i,blackPos), Figure::BlackPawn);
        _model->add(figure);
        figure = new Figure(QPoint(i,whitePos), Figure::WhitePawn);
        _model->add(figure);
    }

    whitePos = 7, blackPos = 0;

    Figure *figure = new Figure(QPoint(0,blackPos), Figure::BlackRook);
    _model->add(figure);
    figure = new Figure(QPoint(1,blackPos), Figure::BlackBishop);
    _model->add(figure);
    figure = new Figure(QPoint(2,blackPos), Figure::BlackKnight);
    _model->add(figure);
    figure = new Figure(QPoint(3,blackPos), Figure::BlackKing);
    _model->add(figure);
    figure = new Figure(QPoint(4,blackPos), Figure::BlackQueen);
    _model->add(figure);
    figure = new Figure(QPoint(5,blackPos), Figure::BlackKnight);
    _model->add(figure);
    figure = new Figure(QPoint(6,blackPos), Figure::BlackBishop);
    _model->add(figure);
    figure = new Figure(QPoint(7,blackPos), Figure::BlackRook);
    _model->add(figure);

    figure = new Figure(QPoint(0,whitePos), Figure::WhiteRook);
    _model->add(figure);
    figure = new Figure(QPoint(1,whitePos), Figure::WhiteBishop);
    _model->add(figure);
    figure = new Figure(QPoint(2,whitePos), Figure::WhiteKnight);
    _model->add(figure);
    figure = new Figure(QPoint(3,whitePos), Figure::WhiteKing);
    _model->add(figure);
    figure = new Figure(QPoint(4,whitePos), Figure::WhiteQueen);
    _model->add(figure);
    figure = new Figure(QPoint(5,whitePos), Figure::WhiteKnight);
    _model->add(figure);
    figure = new Figure(QPoint(6,whitePos), Figure::WhiteBishop);
    _model->add(figure);
    figure = new Figure(QPoint(7,whitePos), Figure::WhiteRook);
    _model->add(figure);
    emit loadPlayedGameWindow();
}

void Controller::leaveGame()
{
    qDebug()<<"leave";
    _model->clear();
    emit loadDefaultWindow();
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

