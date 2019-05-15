#ifndef EDGEBLUREFFECT_H
#define EDGEBLUREFFECT_H

#include <QGraphicsEffect>
#include <QPainter>
#include <QDebug>


QPoint pts[8] = {
    QPoint(-1, -1),
    QPoint(0, -1),
    QPoint(1, -1),
    QPoint(-1, 0),
    QPoint(1, 0),
    QPoint(-1, 1),
    QPoint(0, 1),
    QPoint(1, 1)
};


class EdgeBlurEffect : public QGraphicsEffect
{
    Q_OBJECT

public:
    explicit EdgeBlurEffect(QObject *parent = NULL) :
        QGraphicsEffect(parent)
    {

    }

    virtual ~EdgeBlurEffect()
    {

    }

    bool isPixelHasTheSameColorWithNeighbors(const QImage &image, int x, int y)
    {
        bool ret = false;


        for (int i = 0; i < 8; ++ i)
        {
            QPoint pt = QPoint(x, y) + pts[i];

            if (image.rect().contains(pt))
            {

            }
            else
            {
                continue;
            }
        }

        return ret;
    }

    void draw(QPainter *painter)
    {
        QPoint offset;
        if (sourceIsPixmap()) {
            // No point in drawing in device coordinates (pixmap will be scaled anyways).
            const QPixmap pixmap = sourcePixmap(Qt::LogicalCoordinates, &offset);
            painter->drawPixmap(offset, pixmap);
        } else {
            // Draw pixmap in device coordinates to avoid pixmap scaling;
            QPixmap pixmap = sourcePixmap(Qt::DeviceCoordinates, &offset);


            QImage originImage = pixmap.toImage();

            QImage image(pixmap.size(), QImage::Format_ARGB32_Premultiplied);
            int w = pixmap.width(), h = pixmap.height();
            for (int x = 0; x < w; ++ x)
            {
                for (int y = 0; y < h; ++ y)
                {
                    if (isPixelHasTheSameColorWithNeighbors(originImage, x, y))
                    {
                        image.setPixel(x, y, originImage.pixel(x, y));
                    }
                    else
                    {
                        image.setPixel(x, y, QColor(Qt::red).rgb());
                    }
                }
            }


            painter->setWorldTransform(QTransform());
            painter->save();
            painter->drawPixmap(offset, QPixmap::fromImage(image));
            painter->restore();
        }
    }
};

#endif // EDGEBLUREFFECT_H
