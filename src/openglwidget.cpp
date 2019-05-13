#include "openglwidget.h"
#include <QSurfaceFormat>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QDebug>

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

    QOpenGLFunctions *f = context()->functions();

    qDebug() << "initializeGL()";
    QSurfaceFormat fmt = QSurfaceFormat::defaultFormat();
    qDebug() << "RenderType = " << fmt.renderableType();
    qDebug() << "SwapBehavior = " << fmt.swapBehavior();
    qDebug() << "Samples = " << fmt.samples();

    qDebug() << "GL_VENDOR = " << QString((char*)f->glGetString(GL_VENDOR));
    qDebug() << "GL_VERSION = " << QString((char*)f->glGetString(GL_VERSION));
    qDebug() << "GL_RENDERER = " << QString((char*)f->glGetString(GL_RENDERER));
    QStringList extensionList = QString((char*)f->glGetString(GL_EXTENSIONS)).split(" ");
    qDebug() << "GL_EXTENSIONS = ";
    for (int i = 0; i < extensionList.size(); ++i)
        qDebug() << extensionList.at(i);

    //f->glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
    //f->glEnable(GL_BLEND);
    //f->glEnable(GL_LINE_SMOOTH);
    //f->glEnable(GL_POINT_SMOOTH);
    //f->glEnable(GL_MULTISAMPLE);
    //f->glEnable(GL_LINE_SMOOTH);
    //f->glHint(GL_LINE_SMOOTH,GL_NICEST);

}

void OpenGLWidget::paintGL()
{

}

void OpenGLWidget::resizeGL(int w, int h)
{

}
