#ifndef COMMONFUNC_H
#define COMMONFUNC_H

#include <QDebug>
#include <QPen>
#include <QBrush>
#include <QImage>
#include <QPixmap>
#include <QIcon>

class CommonFunc
{
public:
    CommonFunc();

    static QIcon generateColorIcon(const QColor &color);
};

#endif // COMMONFUNC_H
