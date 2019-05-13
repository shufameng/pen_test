#include "additemthread.h"
#include "scene.h"


AddItemThread::AddItemThread(QObject *parent) :
    QThread(parent)
{
    mScene = NULL;
}

AddItemThread::~AddItemThread()
{

}

void AddItemThread::run()
{
    if (!mScene)
        return;

    mScene->addLine(mLine);
}
