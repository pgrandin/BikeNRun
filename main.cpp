#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "bikenrun.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    BikeNRun bikenrun;
    engine.rootContext()->setContextProperty("bikenrun", &bikenrun);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
