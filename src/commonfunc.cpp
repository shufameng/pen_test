#include "commonfunc.h"

CommonFunc::CommonFunc()
{

}

QIcon CommonFunc::generateColorIcon(const QColor &color)
{
    QImage img(32, 32, QImage::Format_RGB32);
    img.fill(color);
    return QIcon(QPixmap::fromImage(img));
}
