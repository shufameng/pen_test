#ifndef ITEMGROUP_H
#define ITEMGROUP_H

#include <QGraphicsItemGroup>
#include <QDebug>

class ItemGroup : public QGraphicsItemGroup
{
public:
    explicit ItemGroup(QGraphicsItem *parent = 0) : QGraphicsItemGroup(parent)
    {
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
    {
        qDebug() << "ItemGroup::paint()";
        QGraphicsItemGroup::paint(painter, option, widget);
    }

    void update(const QRectF &rect)
    {
        qDebug() << "ItemGroup::update";
        QGraphicsItemGroup::update(rect);
    }
};

#endif // ITEMGROUP_H
