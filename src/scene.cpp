#include "scene.h"
#include "additemthread.h"
#include "items.h"
#include <QImage>
#include "edgeblureffect.h"
#include "itemgroup.h"

#include "view.h"
#include <QGraphicsPathItem>


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

        // Collect items
        mLastCreatedLineItems.clear();

        // Remember mouse button status
        mIsLButtonOnPress = true;
        mLButtonPressScenePos = mLButtonScenePos = sp;

        // Draw it
        if (Pen_DrawStraightLine == mTool)
        {

        }
        else if (Pen_DrawPoints == mTool)
        {
            mlastCreatedPointItems.clear();
            mlastCreatedPointItems.append(_addPoint(sp));
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
            if (QLineF(mLButtonScenePos, sp).length() >= mMinLineLength)
            {
                LineItem *item = _addLine(QLineF(mLButtonScenePos, sp));

                mLastCreatedLineItems.append(item);
                // Remember left mouse button last position
                mLButtonScenePos = sp;
            }
        }
        else if (Pen_DrawPoints == mTool)
        {
            if (QLineF(mLButtonScenePos, sp).length() >= 0)
            {
                mlastCreatedPointItems.append(_addPoint(sp));
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

        ItemGroup *group = new ItemGroup;
        for (int i = 0; i < mLastCreatedLineItems.size(); ++i)
        {
            group->addToGroup(mLastCreatedLineItems[i]);
        }
        addItem(group);


//        QGraphicsView *v = views().first();
//        v->viewport()->update(v->mapFromScene(group->boundingRect()));


        if (Pen_DrawStraightLine == mTool)
        {
//            QGraphicsBlurEffect *effect = new QGraphicsBlurEffect;
//            effect->setBlurHints(QGraphicsBlurEffect::PerformanceHint);
//            effect->setBlurRadius(mBlurRadius);

            EdgeBlurEffect *effect = new EdgeBlurEffect;

            //BlurEffect *effect  = new BlurEffect;

            group->setGraphicsEffect(effect);

        }
        else if (Pen_DrawPoints == mTool)
        {
            QPainterPath path;

            switch (mConnectPointsMethod)
            {
            case StraightConnect:
            {
                for (int i = 0; i < mLastCollectedPoints.size(); ++ i) {
                    if (0 == i) {
                        path.moveTo(mLastCollectedPoints.at(i));
                    } else {
                        path.lineTo(mLastCollectedPoints.at(i));
                    }
                }
            }
                break;
            case CurveConnect:
            {
                for (int i = 0; i + 2 < mLastCollectedPoints.size(); i += 2) {
                    if (0 == i) {
                        path.moveTo(mLastCollectedPoints.at(i));
                    }
                    path.quadTo(mLastCollectedPoints.at(i + 1), mLastCollectedPoints.at(i + 2));
                }
            }
                break;
            case CurveConnectMidWay:
            {
                QPointF current, next;
                for (int i = 0; i + 1 < mLastCollectedPoints.size(); ++ i) {

                    current = mLastCollectedPoints.at(i);
                    next = mLastCollectedPoints.at(i + 1);

                    if (0 == i) {
                        path.moveTo(current);
                        path.lineTo((current + next) / 2);
                    } else {
                        path.quadTo(current, (current + next) / 2);
                    }

                }
            }
                break;
            default:
                break;
            }

            // add pathitem to scene
            QGraphicsPathItem *item = addPath(path);
            item->setPen(toolPen());

            // delete points items

            PointItem *pointItem = NULL;
            for (int i = 0; i < mlastCreatedPointItems.size(); ++ i)
            {
                pointItem = mlastCreatedPointItems[i];

                removeItem(pointItem);
            }

        }
    }
}

LineItem *Scene::_addLine(const QLineF &line)
{
    LineItem *item = new LineItem(line);
    item->setPen(toolPen());
    addItem(item);

    return item;
}

PointItem *Scene::_addPoint(const QPointF &point)
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

void Scene::saveAs(const QString &filePath)
{
    QGraphicsItemGroup *g = createItemGroup(items());
    QRectF r = g->boundingRect();

    QImage image(r.size().toSize(), QImage::Format_RGB32);
    QPainter painter(&image);
    painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing);
    render(&painter, image.rect(), r);

    image.save(filePath);

//    Pixel::Bitmap bitmap;
//    bitmap.Load(filePath.toLocal8Bit().constData());
//    bitmap.SetAntiAliasing(Pixel::AA_HIGH);

}


void Scene::init()
{
    setSceneRect(0, 0, 1920, 1080);

    mToolPen.setStyle(Qt::SolidLine);
    mToolPen.setCapStyle(Qt::RoundCap);
    mToolPen.setJoinStyle(Qt::RoundJoin);
    mToolPen.setColor(Qt::white);
    mToolPen.setWidth(3);

    mTool = Pen_DrawPoints;
    mConnectPointsMethod = CurveConnect;
    mIsLButtonOnPress = false;

    QBrush b;
    b.setStyle(Qt::SolidPattern);
    b.setColor(Qt::black);
    setBackgroundBrush(b);

    mBlurRadius = 1;
    mMinLineLength = 1;
}
