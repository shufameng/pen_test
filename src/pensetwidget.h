#ifndef PENSETWIDGET_H
#define PENSETWIDGET_H

#include <QWidget>

namespace Ui {
class PenSetWidget;
}

class PenSetWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PenSetWidget(QWidget *parent = 0);
    ~PenSetWidget();
    Ui::PenSetWidget *ui;
};

#endif // PENSETWIDGET_H
