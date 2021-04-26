#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "chesscom.h"
#include <QQmlComponent>
#include <QDebug>
int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    ChessCom chesscom;
    engine.rootContext()->setContextProperty("chesscom", &chesscom);


    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    QQmlComponent component(&engine, QUrl(QStringLiteral("qrc:/chessPiece.qml")));

    return app.exec();
}
