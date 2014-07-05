#include <QQuickPaintedItem>
#include <QDebug>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
class ScreenAreaOpenGL : public QQuickItem
{
    Q_OBJECT

public:
    ScreenAreaOpenGL();
    ~ScreenAreaOpenGL();
private slots:
    void handleWindowChanged(QQuickWindow *win);
    void paint();

private:
    QOpenGLShaderProgram * m_program;
    QOpenGLTexture * m_texture;
};
