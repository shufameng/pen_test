#include "pensetwidget.h"
#include "ui_pensetwidget.h"

PenSetWidget::PenSetWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PenSetWidget)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowCloseButtonHint | Qt::Tool);
    setWindowTitle(QString::fromLocal8Bit("�������"));
}

PenSetWidget::~PenSetWidget()
{
    delete ui;
}

