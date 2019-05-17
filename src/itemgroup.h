#ifndef ITEMGROUP_H
#define ITEMGROUP_H

#include "items.h"
#include <QGraphicsItemGroup>
#include <QDebug>

class ItemGroup : public QGraphicsItemGroup
{
public:

    explicit ItemGroup(QGraphicsItem *parent = 0) : QGraphicsItemGroup(parent)
    {
        mId = LineItem::sg_max_lineitem_id ++;
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
    {
        qDebug() << QString("ItemGroup::paint(), itemId == %1").arg(id());
        QGraphicsItemGroup::paint(painter, option, widget);
    }

    void update(const QRectF &rect)
    {
        qDebug() << QString("ItemGroup::update, itemId = %1").arg(id());
        QGraphicsItemGroup::update(rect);
    }

    int id() const
    {
        return mId;
    }

private:
    int mId;
};

#endif // ITEMGROUP_H
