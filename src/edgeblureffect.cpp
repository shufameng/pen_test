#include "edgeblureffect.h"

QPoint pts[]  = {
    QPoint(-1, -1),
    QPoint(0, -1),
    QPoint(1, -1),
    QPoint(-1, 0),
    QPoint(1, 0),
    QPoint(-1, 1),
    QPoint(0, 1),
    QPoint(1, 1),
    QPoint(0, 0)
};

QColor get_average_color_1(const int x, const int y, const QImage &image)
{
    QPoint ct(x, y);
    QRect imageRect = image.rect();
    int count = 0;
    int a, r, g, b;

//    QRgb ctRgb = image.pixel(ct);
//    if (ctRgb == image.pixel(ct + QPoint(-1, 0)) && ctRgb == image.pixel(ct + QPoint(1, 0)))
//        return QColor(ctRgb);
//    if (ctRgb == image.pixel(ct + QPoint(0, -1)) && ctRgb == image.pixel(ct + QPoint(0, 1)))
//        return QColor(ctRgb);

    a = r = g = b = 0;

    for (int i = 0; i < 9; ++ i)
    {
        QPoint p = ct + pts[i];

        if (imageRect.contains(p))
        {
            QColor c(image.pixel(p));

            a += c.alpha();
            r += c.red();
            g += c.green();
            b += c.blue();

            ++ count;
        }
    }

    return QColor(r/count, g/count, b/count, a/count);
}

QColor get_average_color_2(const int x, const int y, const int radius, const QImage &image)
{
    QRect imageRect = image.rect();
    int count = 0;
    int a, r, g, b;
    a = r = g = b = 0;

    QRgb ctRgb = image.pixel(x, y);
    QPoint left(x-1, y), right(x+1, y), top(x, y-1), bot(x, y+1);
    if (imageRect.contains(left) && imageRect.contains(right))
        if (ctRgb == image.pixel(left) && ctRgb == image.pixel(right))
            return QColor(ctRgb);

    if (imageRect.contains(top) && imageRect.contains(bot))
        if (ctRgb == image.pixel(top) && ctRgb == image.pixel(bot))
            return QColor(ctRgb);

    for (int x1 = -radius; x1 <= radius; ++ x1)
    {
        for (int y1 = -radius; y1 <= radius; ++ y1)
        {
            QPoint p(x + x1, y + y1);

            if (imageRect.contains(p))
            {
                QColor color(image.pixel(p));

                a += color.alpha();
                r += color.red();
                g += color.green();
                b += color.blue();

                ++ count;
            }
        }
    }

    return QColor(r/count, g/count, b/count, a/count);
}

void EdgeBlurEffect::blur_1(const QImage &in, QImage &out)
{
    int w = in.width(), h = in.height();

    for (int x = 0; x < w; ++ x)
    {
        for (int y = 0; y < h; ++ y)
        {
            out.setPixelColor(x, y, get_average_color_1(x, y, in));
        }
    }
}

void EdgeBlurEffect::blur_2(int radius, const QImage &in, QImage &out)
{
    int w = in.width(), h = in.height();

    for (int x = 0; x < w; ++ x)
    {
        for (int y = 0; y < h; ++ y)
        {
            out.setPixelColor(x, y, get_average_color_2(x, y, radius, in));
        }
    }
}

void EdgeBlurEffect::draw(QPainter *painter)
{
    QPoint offset;
    if (sourceIsPixmap()) {
        // No point in drawing in device coordinates (pixmap will be scaled anyways).
        const QPixmap pixmap = sourcePixmap(Qt::LogicalCoordinates, &offset);
        painter->drawPixmap(offset, pixmap);
    } else {
        // Draw pixmap in device coordinates to avoid pixmap scaling;
        QPixmap pixmap = sourcePixmap(Qt::DeviceCoordinates, &offset);//pixmap.save("1111.jpg");
        QImage in = pixmap.toImage();
        QImage out(in.size(), in.format());
        blur_2(1, in, out);out.save("1111.png");
        //blur_1(originImage, img);

        painter->setWorldTransform(QTransform());
        painter->save();
        painter->drawPixmap(offset, QPixmap::fromImage(out));
        //painter->drawPixmap(offset, pixmap);
        painter->restore();
    }
}























