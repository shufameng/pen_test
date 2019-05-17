#ifndef ITEMS_H
#define ITEMS_H

#include <QGraphicsLineItem>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QPen>
#include <QBrush>
#include <QGraphicsBlurEffect>
#include <QGraphicsOpacityEffect>

class LineItem : public QGraphicsLineItem
{
public:
    static int sg_max_lineitem_id;

    explicit LineItem(QGraphicsItem *parent = 0) :
        QGraphicsLineItem(parent)
    {
        mId = sg_max_lineitem_id ++;
    }
    explicit LineItem(const QLineF &li, QGraphicsItem *parent = 0) :
        QGraphicsLineItem(li, parent)
    {}
    virtual ~LineItem()
    {}

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
    {
        painter->setRenderHints(QPainter::Antialiasing);
        QGraphicsLineItem::paint(painter, option, widget);
    }

    int id() const
    {
        return mId;
    }

private:
    int mId;
};


class PointItem : public QGraphicsItem
{
public:
    explicit PointItem(QGraphicsItem *parent = 0)
    {}
    explicit PointItem(const QPointF &p, QGraphicsItem *parent = 0)
    {
        setPoint(p);
    }

    virtual ~PointItem()
    {}

    void setPoint(const QPointF &p)
    {
        prepareGeometryChange();
        mPoint = p;
        update();
    }

    QPointF point() const
    {
        return mPoint;
    }

    void setPen(const QPen &p)
    {
        mPen = p;
        update();
    }

    QPen pen() const
    {
        return mPen;
    }

    QRectF boundingRect() const
    {
        qreal halfpw = pen().style() == Qt::NoPen ? 0 : pen().widthF()/2;
        return QRectF(mPoint - QPointF(halfpw, halfpw), mPoint + QPointF(halfpw, halfpw));
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
    {
        painter->setRenderHints(QPainter::Antialiasing);
        painter->setPen(mPen);
        painter->drawPoint(mPoint);
    }

private:
    QPointF mPoint;
    QPen mPen;
};

#endif // ITEMS_H
