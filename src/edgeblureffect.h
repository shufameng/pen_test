#ifndef EDGEBLUREFFECT_H
#define EDGEBLUREFFECT_H

#include <QGraphicsEffect>
#include <QPainter>
#include <QDebug>
#include <QDebug>




class EdgeBlurEffect : public QGraphicsEffect
{
    Q_OBJECT

public:

    static void blur_1(const QImage &in, QImage &out);
    static void blur_2(int radius, const QImage &in, QImage &out);


    explicit EdgeBlurEffect(QObject *parent = NULL) :
        QGraphicsEffect(parent)
    {

    }

    virtual ~EdgeBlurEffect()
    {

    }


    void draw(QPainter *painter);
};

#endif // EDGEBLUREFFECT_H
