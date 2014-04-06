#include <QDebug>
#include <QtGui/QGuiApplication>
#include <QtQuick/QQuickView>
#include <QQmlEngine>
#include <QQmlContext>
#include "ScreenArea.h"

#include "window.h"
Window * w;
int main(int argc, char ** argv) {
    qDebug() << "Hello vgba";
    QGuiApplication a(argc, argv);
    QQuickView view;

    w = new Window();
    w->bLoadROM("./1.gba");

    view.engine()->rootContext()->setContextProperty("window", w);
    qmlRegisterType<ScreenArea>("QVBA", 0, 1, "ScreenArea");
    view.setSource(QUrl::fromLocalFile("qml/main.qml"));
    view.show();
    return a.exec();
}
