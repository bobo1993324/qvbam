#include <QQuickPaintedItem>
#include <QDebug>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLFunctions>
class ScreenAreaOpenGL : public QQuickItem, protected QOpenGLFunctions
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
