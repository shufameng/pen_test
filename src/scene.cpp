#include "scene.h"


Scene::Scene(QObject *parent) :
    QGraphicsScene(parent)
{
    init();
}

Scene::~Scene()
{

}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
    if (e->button() & Qt::LeftButton)
    {
        QPointF sp = e->scenePos();

        mIsLButtonOnPress = true;
        mLButtonPressScenePos = mLButtonScenePos = sp;

        drawBegin(e);
    }
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *e)
{
    if (mIsLButtonOnPress)
    {
        drawUpdate(e);

        mLButtonScenePos = e->scenePos();
    }
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *e)
{
    if (e->button() & Qt::LeftButton)
    {
        mIsLButtonOnPress = false;

        drawEnd(e);
    }
}

void Scene::drawBegin(QGraphicsSceneMouseEvent *e)
{
    if (mTool == Pen1)
    {
        mLastCollectedPoints.clear();
        mLastCollectedPoints.append(e->scenePos());
    }
}

void Scene::drawUpdate(QGraphicsSceneMouseEvent *e)
{
    if (mTool == Pen1)
    {
        mLastCollectedPoints.append(e->scenePos());

        addLineItem(QLineF(mLButtonScenePos, e->scenePos()));
    }
}

void Scene::drawEnd(QGraphicsSceneMouseEvent *e)
{
    if (mTool == Pen1)
    {
        mLastCollectedPoints.append(e->scenePos());

        mPointsList.append(mLastCollectedPoints);
    }
}

QGraphicsLineItem *Scene::addLineItem(const QLineF &line)
{
    QGraphicsLineItem *item = new QGraphicsLineItem(line);
    item->setPen(toolPen());
    addItem(item);

    return item;
}

void Scene::setPointsList(QList<QList<QPointF> > pointsList)
{
    clear();
    mPointsList.clear();

    for (int i = 0; i < pointsList.size(); ++i)
    {
        QList<QPointF> points = pointsList.at(i);
        mPointsList.append(points);

        for (int j = 0; j + 1 < points.size(); ++j)
        {
            addLineItem(QLineF(points.at(j), points.at(j + 1)));
        }
    }
}

QList<QList<QPointF> > Scene::pointsList() const
{
    return mPointsList;
}

void Scene::clear()
{
    QGraphicsScene::clear();
    mPointsList.clear();
}


void Scene::init()
{
    setSceneRect(0, 0, 1920, 1080);

    mToolPen.setStyle(Qt::SolidLine);
    mToolPen.setCapStyle(Qt::RoundCap);
    mToolPen.setJoinStyle(Qt::RoundJoin);
    mToolPen.setColor(Qt::red);
    mToolPen.setWidth(2);

    mTool = Pen1;
    mIsLButtonOnPress = false;

    QBrush b;
    b.setStyle(Qt::SolidPattern);
    b.setColor(Qt::black);
    setBackgroundBrush(b);
}
