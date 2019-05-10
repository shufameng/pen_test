#include "penwindow.h"
#include "ui_penwindow.h"
#include "view.h"
#include "scene.h"
#include <QHBoxLayout>
#include <QDockWidget>
#include "pensetwidget.h"
#include "ui_pensetwidget.h"
#include <QColorDialog>
#include "commonfunc.h"

PenWindow::PenWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PenWindow)
{
    ui->setupUi(this);

    // views
    mRasterView = new View();
    mRasterView->setScene(new Scene());

    mOpenGLView = new View(true);
    mOpenGLView->setScene(new Scene());

    QHBoxLayout *hlay = new QHBoxLayout(centralWidget());
    hlay->addWidget(mRasterView);
    hlay->addWidget(mOpenGLView);

    // PenSetWidget
    mPenSetWgt = new PenSetWidget(this);
    mPenSetWgt->show();
    connect(mPenSetWgt->ui->toolButtonPenColor, SIGNAL(clicked()), this, SLOT(onPenColor()));
    connect(mPenSetWgt->ui->spinBoxPenWidth, SIGNAL(valueChanged(int)), this, SLOT(onPenWidthChanged(int)));
    connect(mPenSetWgt->ui->pushButton_o2r, SIGNAL(clicked()), this, SLOT(onO2R()));
    connect(mPenSetWgt->ui->pushButton_r2o, SIGNAL(clicked()), this, SLOT(onR2O()));
    connect(mPenSetWgt->ui->pushButtonCleanAll, SIGNAL(clicked()), this, SLOT(onCleanAll()));

    //
    updateUI();
}

PenWindow::~PenWindow()
{
    delete ui;
}

void PenWindow::onPenColor()
{
    Scene *s = mRasterView->getScene();
    if (!s)
        return;

    QColor cl = QColorDialog::getColor(s->toolPen().color());
    if (cl.isValid())
    {
        QPen p = getPen();
        p.setColor(cl);

        setPen(p);
    }
}

void PenWindow::onPenWidthChanged(int w)
{
    QPen p = getPen();
    p.setWidth(w);
    setPen(p);
}

void PenWindow::onR2O()
{
    mOpenGLView->getScene()->setPointsList(mRasterView->getScene()->pointsList());
}

void PenWindow::onO2R()
{
    mRasterView->getScene()->setPointsList(mOpenGLView->getScene()->pointsList());
}

void PenWindow::onCleanAll()
{
    mRasterView->getScene()->clear();
    mOpenGLView->getScene()->clear();
}

QPen PenWindow::getPen()
{
    return mRasterView->getScene()->toolPen();
}

void PenWindow::setPen(const QPen &p)
{
    mRasterView->getScene()->setToolPen(p);
    mOpenGLView->getScene()->setToolPen(p);
}

void PenWindow::updateUI()
{
    mPenSetWgt->ui->spinBoxPenWidth->setValue(getPen().width());
    mPenSetWgt->ui->toolButtonPenColor->setIcon(CommonFunc::generateColorIcon(getPen().color()));
}
