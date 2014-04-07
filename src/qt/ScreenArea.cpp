#include "ScreenArea.h"

extern u8 *pix;
extern Window * w;

ScreenArea::ScreenArea() {
    setAntialiasing(false);
    connect(this, SIGNAL(widthChanged()), this, SLOT(ssetScale()));
}

void ScreenArea::paint(QPainter *painter) {
//    painter->fillRect(0, 0, w->m_iScreenHeight, w->m_iScreenWidth, Qt::black);
    for (int i = 0; i < w->m_iScreenHeight; i++) {
        for (int j = 0; j < w->m_iScreenWidth; j++) {
            u8* currentPix = pix + 4 * ((w->m_iScreenWidth + 1) * (i + 1) + j);
            painter->fillRect(j, i, 1, 1, QColor(*(currentPix + 2), *(currentPix + 1), *currentPix));
        }
    }
}

void ScreenArea::ssetScale() {
    setContentsScale(width() / w->m_iScreenWidth);
}
