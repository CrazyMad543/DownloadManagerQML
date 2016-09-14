#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include "data.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<Data>("CrazzyMad.data", 1, 0, "Data");
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

