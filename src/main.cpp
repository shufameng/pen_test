#include "penwindow.h"
#include <QApplication>
#include <QSurfaceFormat>
#include <QTouchDevice>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_UseOpenGLES);

    QApplication a(argc, argv);

    QSurfaceFormat fmt;
    fmt.setDepthBufferSize(24);
    fmt.setStencilBufferSize(8);
    fmt.setSamples(8);
    fmt.setProfile(QSurfaceFormat::CoreProfile);
    //fmt.setRenderableType(QSurfaceFormat::OpenGLES);
    QSurfaceFormat::setDefaultFormat(fmt);


    QList<const QTouchDevice*> dvcs = QTouchDevice::devices();
    for (int i = 0; i < dvcs.size(); ++i)
    {
        qDebug() << dvcs.at(i)->name();
        qDebug() << dvcs.at(i)->type();
        qDebug() << dvcs.at(i)->maximumTouchPoints();
        qDebug() << dvcs.at(i)->capabilities();
    }

    PenWindow w;
    w.showMaximized();

    return a.exec();
}
