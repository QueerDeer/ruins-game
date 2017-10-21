#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <handlersignals.h>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    srand (time(NULL));

    QObject* root = engine.rootObjects()[0];

    HandlerSignals *handlerSignals= new HandlerSignals(root);

    QObject::connect(root, SIGNAL(qmlChangeField(QString, QString)),
                     handlerSignals, SLOT(changeField(QString, QString)));

    QObject::connect(root, SIGNAL(qmlGenerateField()),
                     handlerSignals, SLOT(generation()));

    QObject::connect(root, SIGNAL(qmlStartEngine()),
                     handlerSignals, SLOT(engine()));

    QObject::connect(root, SIGNAL(qmlCreateSoldier(QString)),
                     handlerSignals, SLOT(createSoldier(QString)));

    QObject::connect(root, SIGNAL(qmlChangeAnimation(QString, QString, QString, QString)),
                     handlerSignals, SLOT(changeAnimation(QString, QString, QString, QString)));

    return app.exec();
}
