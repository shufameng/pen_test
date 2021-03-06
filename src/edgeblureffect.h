#ifndef EDGEBLUREFFECT_H
#define EDGEBLUREFFECT_H

#include <QGraphicsEffect>
#include <QPainter>
#include <QGraphicsBlurEffect>
#include <QDebug>

#include "items.h"

class EdgeBlurEffect : public QGraphicsEffect
{
    Q_OBJECT

public:

    static void blur_1(const QImage &in, QImage &out);
    static void blur_2(int radius, const QImage &in, QImage &out);
    static void blur_3(const QImage &in, QImage &out);


    explicit EdgeBlurEffect(QObject *parent = NULL) :
        QGraphicsEffect(parent)
    {
        mId = LineItem::sg_max_lineitem_id ++;
    }

    virtual ~EdgeBlurEffect()
    {

    }


    void draw(QPainter *painter);

    int id() const {
        return mId;
    }

private:
    int mId;
};

class BlurEffect : public QGraphicsBlurEffect
{
    Q_OBJECT

public:
    explicit BlurEffect(QObject *parent = NULL) :
        QGraphicsBlurEffect(parent)
    {

    }

    void draw(QPainter *painter)
    {
        qDebug() << "BlurEffect::Draw()";
        QGraphicsBlurEffect::draw(painter);
    }
};

#endif // EDGEBLUREFFECT_H
