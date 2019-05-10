#include "openglwidget.h"
#include <QSurfaceFormat>
#include <QOpenGLContext>
#include <QOpenGLFunctions>

OpenGLWidget::OpenGLWidget(QWidget *parent) :
    QOpenGLWidget(parent)
{

}

OpenGLWidget::~OpenGLWidget()
{

}

void OpenGLWidget::initializeGL()
{
//    QSurfaceFormat fmt;
//    fmt.setDepthBufferSize(24);
//    fmt.setStencilBufferSize(8);
//    fmt.setSamples(8);
//    fmt.setProfile(QSurfaceFormat::CoreProfile);
//    fmt.setRenderableType(QSurfaceFormat::OpenGLES);
//    context()->setFormat(fmt);
}

void OpenGLWidget::paintGL()
{

}

void OpenGLWidget::resizeGL(int w, int h)
{

}
