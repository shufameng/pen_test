#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QPen>
#include <QBrush>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>
#include <QDebug>

class LineItem;
class PointItem;
class Scene : public QGraphicsScene
{
    Q_OBJECT

public:
    enum Tool
    {
        // »­Ö±Ïß
        Pen_DrawStraightLine,
        // »­µã
        Pen_DrawPoints
    };

    enum ConnectPointsMethod
    {
        NoConnect,
        StraightConnect,
        CurveConnect,
        CurveConnectMidWay,
        CurveConnectMidWay_Use_PainterPath
    };

    explicit Scene(QObject *parent = 0);
    virtual ~Scene();

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *e);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *e);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *e);

    LineItem *_addLine(const QLineF &line);
    PointItem *_addPoint(const QPointF &point);
    QGraphicsPathItem *_addPath(const QPainterPath &path);

public slots:
    void setToolPen(const QPen &p)
    {
        mToolPen = p;
    }

    QPen toolPen() const
    {
        return mToolPen;
    }

    void setToolBrush(const QBrush &b)
    {
        mToolBrush = b;
    }

    QBrush toolBrush() const
    {
        return mToolBrush;
    }

    void setTool(Tool t)
    {
        mTool = t;
    }

    Tool tool() const
    {
        return mTool;
    }


    void setPointsList(QList<QList<QPointF>> pointsList);
    QList<QList<QPointF>> pointsList() const;

    void clear();

    void saveAs(const QString &filePath);

    qreal blurRadius() const
    {
        return mBlurRadius;
    }

    void setBlurRadius(qreal radius)
    {
        mBlurRadius = radius;
    }

    qreal minLineLength() const
    {
        return mMinLineLength;
    }

    void setMinLineLength(qreal len)
    {
        mMinLineLength = len;
    }

    void setConnectPointsMethod(ConnectPointsMethod method)
    {
        mConnectPointsMethod = method;
    }

    ConnectPointsMethod connectPointsMethod() const
    {
        return mConnectPointsMethod;
    }

private:
    void init();

    QPen mToolPen;
    QBrush mToolBrush;
    Tool mTool;
    ConnectPointsMethod mConnectPointsMethod;

    bool mIsLButtonOnPress;
    QPointF mLButtonScenePos;
    QPointF mLButtonPressScenePos;

    QList<QList<QPointF>> mPointsList;
    QList<QPointF> mLastCollectedPoints;
    QList<LineItem*> mLastCreatedLineItems;

    QList<PointItem*> mlastCreatedPointItems;

    qreal mBlurRadius;
    qreal mMinLineLength;
};

#endif // SCENE_H
