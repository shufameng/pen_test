#include "edgeblureffect.h"
#include <QtMath>

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

int kernel_3[][3] = {
    {1, 2, 1},
    {2, 4, 2},
    {1, 2, 1}
};

qreal gauss_func_1d(const qreal x, const qreal sigmal)
{
    return exp(-(x*x)/(2*sigmal*sigmal) / sqrtf(2*M_PI)*sigmal);
}

qreal guass_func_2d(const qreal x, const qreal y, const qreal sigmal)
{
    return (exp(-1 * (pow(x, 2) + pow(y, 2)) / (pow(sigmal, 2)*2)) / (2*M_PI*pow(sigmal, 2)));
}

QColor get_average_color_1(const int x, const int y, const QImage &image)
{
    QPoint ct(x, y);
    QRect imageRect = image.rect();
    int count = 0;
    int a, r, g, b;

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

QColor get_average_color_2(const int x, const int y, const int radius, const QImage &image)
{
    QRect imageRect = image.rect();
    int count = 0;
    int a, r, g, b;
    a = r = g = b = 0;

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

QColor get_average_color_3(const int x, const int y, const QImage &image)
{
    QRect imageRect = image.rect();
    int count = 0;
    int a, r, g, b;
    a = r = g = b = 0;
    int radius = 1;

    for (int x1 = -radius; x1 <= radius; ++ x1)
    {
        for (int y1 = -radius; y1 <= radius; ++ y1)
        {
            QPoint p(x + x1, y + y1);

            if (imageRect.contains(p))
            {
                QColor color;
                color.setRgba(image.pixel(p));
                int k = kernel_3[y1 + 1][x1 + 1];

                a += color.alpha()*k;
                r += color.red()*k;
                g += color.green()*k;
                b += color.blue()*k;

                count += k;
            }
        }
    }

    return QColor(r/count, g/count, b/count, a/count);
}

void EdgeBlurEffect::blur_3(const QImage &in, QImage &out)
{
    int w = in.width(), h = in.height();

    for (int x = 0; x < w; ++ x)
    {
        for (int y = 0; y < h; ++ y)
        {
            out.setPixelColor(x, y, get_average_color_3(x, y, in));
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
        QPixmap pixmap = sourcePixmap(Qt::DeviceCoordinates, &offset);
        //pixmap.save("1111.jpg");

        qDebug() << QString("EdgeBlurEffect::draw(), effectId = %1").arg(id());
        qDebug() << kernel_3[1][2];

        QImage in = pixmap.toImage();
        QImage out(in.size(), in.format());
        blur_3(in, out);
        //out.save("1111.png");
        //blur_1(originImage, img);

        painter->setWorldTransform(QTransform());
        painter->save();
        painter->drawPixmap(offset, QPixmap::fromImage(out));
        //painter->drawPixmap(offset, pixmap);
        painter->restore();
    }
}























