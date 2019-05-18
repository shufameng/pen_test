#include "stackedwidget.h"
#include "view.h"
#include "scene.h"

StackedWidget::StackedWidget(QWidget *parent) :
    QStackedWidget(parent)
{
    View *v = new View;
    v->setScene(new Scene);
    addWidget(v);
}
