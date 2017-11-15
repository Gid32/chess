#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "controller.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QQmlContext *context = engine.rootContext();
    Controller controller(context);

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    controller.initConnection(engine.rootObjects().first());

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
