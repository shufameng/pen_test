#include "view.h"
#include "openglwidget.h"
#include "scene.h"
#include <QDebug>
#include <QPainter>

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

    qDebug() << viewportUpdateMode();
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

void View::paintEvent(QPaintEvent *e)
{//qDebug() << "View::paintEvent(QPaintEvent *e)";
//    QImage image(400, 600, QImage::Format_RGBA8888);
//    QPainter painter(this);
//    painter.setPen(QPen(Qt::red));
//    painter.drawLine(QPointF(5, 5), QPointF(100, 100));
    return QGraphicsView::paintEvent(e);
}

void View::init()
{
    mUseOpenGL = false;
    setResizeAnchor(QGraphicsView::NoAnchor);
    //setViewportUpdateMode(QGraphicsView::NoViewportUpdate);
    setRenderHints(QPainter::Antialiasing);
    //setCacheMode(QGraphicsView::CacheBackground);
}
