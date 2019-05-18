#ifndef STACKEDWIDGET_H
#define STACKEDWIDGET_H

#include <QStackedWidget>

class View;
class Scene;

class StackedWidget : public QStackedWidget
{
    Q_OBJECT

public:
    explicit StackedWidget(QWidget *parent = 0);



};

#endif // STACKEDWIDGET_H
