#include "scene.h"
#include "additemthread.h"
#include "items.h"


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

        // Collect point
        mLastCollectedPoints.clear();
        mLastCollectedPoints.append(e->scenePos());

        // Remember mouse button status
        mIsLButtonOnPress = true;
        mLButtonPressScenePos = mLButtonScenePos = sp;

        // Draw it
        if (Pen_DrawStraightLine == mTool)
        {

        }
    }
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *e)
{
    if (mIsLButtonOnPress)
    {
        QPointF sp = e->scenePos();

        // Collect point
        mLastCollectedPoints.append(sp);

        // Draw it
        if (Pen_DrawStraightLine == mTool)
        {
            if (QLineF(mLButtonScenePos, sp).length() >= 1)
            {
                _addLine(QLineF(mLButtonScenePos, sp));
                // Remember left mouse button last position
                mLButtonScenePos = sp;
            }
        }
        else if (Pen_DrawPoints == mTool)
        {
            if (QLineF(mLButtonScenePos, sp).length() >= mToolPen.widthF())
            {
                _addPoint(sp);
                mLButtonPressScenePos = sp;
            }
        }
    }
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *e)
{
    if (e->button() & Qt::LeftButton)
    {
        // Remember mouse button status
        mIsLButtonOnPress = false;

        // Collect point
        mLastCollectedPoints.append(e->scenePos());
        mPointsList.append(mLastCollectedPoints);
    }
}

QGraphicsLineItem *Scene::_addLine(const QLineF &line)
{
    LineItem *item = new LineItem(line);
    item->setPen(toolPen());
    addItem(item);

    return item;
}

QGraphicsItem *Scene::_addPoint(const QPointF &point)
{
    PointItem *item = new PointItem(point);
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
            _addLine(QLineF(points.at(j), points.at(j + 1)));
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
    mToolPen.setColor(Qt::white);
    mToolPen.setWidth(2);

    mTool = Pen_DrawStraightLine;
    mIsLButtonOnPress = false;

    QBrush b;
    b.setStyle(Qt::SolidPattern);
    b.setColor(Qt::black);
    setBackgroundBrush(b);
}
