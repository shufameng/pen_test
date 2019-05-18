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
    fmt.setSamples(8);
    fmt.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
    fmt.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(fmt);


//    QList<const QTouchDevice*> dvcs = QTouchDevice::devices();
//    for (int i = 0; i < dvcs.size(); ++i)
//    {
//        qDebug() << dvcs.at(i)->name();
//        qDebug() << dvcs.at(i)->type();
//        qDebug() << dvcs.at(i)->maximumTouchPoints();
//        qDebug() << dvcs.at(i)->capabilities();
//    }

    PenWindow w;
    w.showMaximized();

    return a.exec();
}
