#ifndef ADDITEMTHREAD_H
#define ADDITEMTHREAD_H

#include <QThread>
#include <QLineF>

class Scene;
class AddItemThread : public QThread
{
    Q_OBJECT

public:
    explicit AddItemThread(QObject *parent = 0);
    virtual ~AddItemThread();

    void setScene(Scene *s)
    {
        mScene = s;
    }

    void setLine(const QLineF &li)
    {
        mLine = li;
    }

protected:
    virtual void run();

private:
    Scene *mScene;
    QLineF mLine;
};

#endif // ADDITEMTHREAD_H
