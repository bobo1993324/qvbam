#include "ScreenAreaOpenGL.h"
#include <QDebug>
#include <QQuickWindow>
#include "GL/gl.h"
#include "../common/Types.h"
#include <QOpenGLPixelTransferOptions>
extern u8 *pix;
ScreenAreaOpenGL::ScreenAreaOpenGL() :
    m_program(0), m_texture(0) {
    connect(this, SIGNAL(windowChanged(QQuickWindow*)), this, SLOT(handleWindowChanged(QQuickWindow*)));
}
ScreenAreaOpenGL::~ScreenAreaOpenGL() {
    if (m_program)
        delete m_program;
}

void ScreenAreaOpenGL::handleWindowChanged(QQuickWindow *win)
{
    if (win) {
        connect(window(), SIGNAL(afterRendering()), this, SLOT(paint()), Qt::DirectConnection);
        win->setClearBeforeRendering(false);
    }
}

void ScreenAreaOpenGL::paint() {
    if (!m_program) {
        m_program = new QOpenGLShaderProgram();
        m_program->addShaderFromSourceCode(QOpenGLShader::Vertex,
                                           "attribute vec2 vertex;"
                                           "varying vec2 coords;"
                                           "void main() {"
                                           "    coords = vertex.xy;"
                                           "    gl_Position = vec4 (vertex.x, vertex.y, 0, 1.0);"
                                           "}");
        m_program->addShaderFromSourceCode(QOpenGLShader::Fragment,
                                           "uniform sampler2D myTexture;"
                                           "varying vec2 coords;"
                                           "void main() {"
                                           "    gl_FragColor = texture2D(myTexture, vec2 (coords.x * 0.5 + 0.5, coords.y * -0.5 + 0.5));"
                                           "}");

        //TODO destroy this in context
        m_texture = new QOpenGLTexture(QOpenGLTexture::Target2D);
        m_texture->setFormat(QOpenGLTexture::RGB8_UNorm);
        m_texture->setSize(241, 160);
        m_texture->setMipLevels(m_texture->maximumMipLevels());
        m_texture->allocateStorage();

        m_program->bindAttributeLocation("vertex", 0);
        m_program->link();
    }
    m_texture->setData(0, QOpenGLTexture::BGRA, QOpenGLTexture::UInt8, pix, 0);

//! [4] //! [5]
    m_program->bind();

    m_program->enableAttributeArray(0);

    float values[] = {
        -1, -1,
        1, -1,
        -1, 1,
        1, 1
    };
    m_program->setAttributeArray(0, GL_FLOAT, values, 2);
    unsigned int textureLocation = m_program->uniformLocation("myTexture");
    m_texture->bind(textureLocation);

    glViewport(this->property("positionFromLeft").toInt(),
               this->property("positionFromBottom").toInt(),
               width(), height());

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    m_program->disableAttributeArray(0);
    m_program->release();
}
