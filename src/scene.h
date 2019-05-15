#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QPen>
#include <QBrush>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>
#include <QDebug>

class LineItem;
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

    explicit Scene(QObject *parent = 0);
    virtual ~Scene();

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *e);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *e);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *e);

    LineItem *_addLine(const QLineF &line);
    QGraphicsItem *_addPoint(const QPointF &point);

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


private:
    void init();

    QPen mToolPen;
    QBrush mToolBrush;
    Tool mTool;

    bool mIsLButtonOnPress;
    QPointF mLButtonScenePos;
    QPointF mLButtonPressScenePos;

    QList<QList<QPointF>> mPointsList;
    QList<QPointF> mLastCollectedPoints;
    QList<LineItem*> mLastCreatedLineItems;

    qreal mBlurRadius;

};

#endif // SCENE_H
