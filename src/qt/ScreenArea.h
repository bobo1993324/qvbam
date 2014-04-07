#include <QQuickPaintedItem>
#include <QDebug>
#include <QPainter>
#include "../common/Types.h"
#include "window.h"
class ScreenArea : public QQuickPaintedItem {
    Q_OBJECT
public:
    ScreenArea();
    void paint(QPainter *painter);
public slots:
    void ssetScale();
};
