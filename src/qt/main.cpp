#include <QDebug>
#include <QObject>
#include <QtGui/QGuiApplication>
#include <QtQuick/QQuickView>
#include <QQmlEngine>
#include <QQmlContext>
#include <csignal>
#include "ScreenArea.h"
#include "window.h"
#include "CustomQQuickView.h"
#include "ScreenAreaOpenGL.h"
#include "FilesModel.h"
#include "QGameSlot.h"
Window * w;
CustomQQuickView * view;
int main(int argc, char ** argv) {
    qDebug() << "Hello vgba";
    QGuiApplication a(argc, argv);
    view = new CustomQQuickView();

    w = new Window();
//    w->bLoadROM("./1.gba");
    FilesModel romsModel;
    view->setResizeMode(QQuickView::SizeRootObjectToView);
    view->engine()->rootContext()->setContextProperty("romsModel", &romsModel);
    view->engine()->rootContext()->setContextProperty("iwindow", w);
    qmlRegisterType<ScreenArea>("QVBA", 0, 1, "ScreenArea");
    qmlRegisterUncreatableType<Window>("QVBA", 0, 1, "WINDOW", "hehe");
    qmlRegisterUncreatableType<QGameSlot>("QVBA", 0, 1, "QGameSlot", "hehe");


    view->setSource(QUrl::fromLocalFile("qml/main.qml"));
    view->show();
    return a.exec();
}
