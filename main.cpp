#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "SystemProvider.h"
#include "processModel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    SystemProvider systemStats;
    ProcessModel processModel;

    QQmlApplicationEngine engine;

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.rootContext()->setContextProperty("systemStats", &systemStats);
    engine.rootContext()->setContextProperty("processModel", &processModel);

    engine.loadFromModule("UberMem", "Main");

    return QCoreApplication::exec();
}
