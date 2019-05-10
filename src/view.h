#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>
#include <QMouseEvent>

class Scene;
class View : public QGraphicsView
{
    Q_OBJECT

public:
    explicit View(QWidget *parent = 0);
    explicit View(bool useOpenGL, QWidget *parent = 0);
    virtual ~View();

    Scene *getScene();

protected:
    virtual void mouseMoveEvent(QMouseEvent *event);

private:
    void init();

    bool mUseOpenGL;
};

#endif // VIEW_H
