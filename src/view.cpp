#include "view.h"
#include "openglwidget.h"
#include "scene.h"
#include <QDebug>

View::View(QWidget *parent) :
    QGraphicsView(parent)
{
    init();

    setWindowFlags(windowFlags());
}

View::View(bool useOpenGL, QWidget *parent)
{
    init();

    mUseOpenGL = useOpenGL;
    if (useOpenGL)
    {
        OpenGLWidget *openglView = new OpenGLWidget(this);
        setViewport(openglView);
    }
}

View::~View()
{

}

Scene *View::getScene()
{
    return dynamic_cast<Scene*>(scene());
}

void View::mouseMoveEvent(QMouseEvent *event)
{
    return QGraphicsView::mouseMoveEvent(event);
}

void View::init()
{
    mUseOpenGL = false;
    setResizeAnchor(QGraphicsView::NoAnchor);
    setRenderHints(QPainter::Antialiasing);
}
