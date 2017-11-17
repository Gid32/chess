#include "controller.h"

Controller::Controller(QQmlContext *context)
{
    _model = new ChessModel();

    context->setContextProperty("chessModel", _model);
    qmlRegisterType<Figure>("cpp", 1, 0, "Figure");
}


void Controller::startGame()
{
    emit loadPlayedGameWindow();
}

void Controller::leaveGame()
{
    _model->clear();
    emit loadDefaultWindow();
}

void Controller::initConnection(QObject *qml)
{
    _qml = qml;
    connect(_qml,SIGNAL(startGame()),
            _model,SLOT(start()));

    connect(this,SIGNAL(loadPlayedGameWindow()),
            _qml,SLOT(loadPlayedGameWindow()));

    connect(_qml,SIGNAL(leaveGame()),
            this,SLOT(leaveGame()));

    connect(this,SIGNAL(loadDefaultWindow()),
            _qml,SLOT(loadDefaultWindow()));

    connect(_model,SIGNAL(started()),
            this,SLOT(startGame()));
}

