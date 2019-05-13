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
    setWindowTitle("Attention: The right side is rendered by OpenGL");

    // views
    mRasterView = new View();
    mRasterView->setScene(mRasterScene = new Scene());

    mOpenGLView = new View(true);
    mOpenGLView->setScene(mOpenGLScene = new Scene());

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

    // Checkable buttons
    QButtonGroup *penTypeButtonGroup = new QButtonGroup(this);
    penTypeButtonGroup->addButton(mPenSetWgt->ui->toolButtonPen_StraightLines);
    penTypeButtonGroup->addButton(mPenSetWgt->ui->toolButtonPen_Points);
    connect(penTypeButtonGroup, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(onPenTypeButtonGroupButtonClicked(QAbstractButton*)));

    //
    updateUI();
}

PenWindow::~PenWindow()
{
    delete ui;
}

void PenWindow::onPenColor()
{
    QColor cl = QColorDialog::getColor(mRasterScene->toolPen().color());
    if (cl.isValid())
    {
        QPen p = mRasterScene->toolPen();
        p.setColor(cl);

        setScenesToolPen(p);
    }
}

void PenWindow::onPenWidthChanged(int w)
{
    QPen p = mRasterScene->toolPen();
    p.setWidth(w);

    setScenesToolPen(p);
}

void PenWindow::onR2O()
{
    mOpenGLScene->setPointsList(mRasterScene->pointsList());
}

void PenWindow::onO2R()
{
   mRasterScene->setPointsList(mOpenGLScene->pointsList());
}

void PenWindow::onCleanAll()
{
    mRasterScene->clear();
    mOpenGLScene->clear();
}

void PenWindow::onPenTypeButtonGroupButtonClicked(QAbstractButton *button)
{
    if (button == mPenSetWgt->ui->toolButtonPen_StraightLines)
    {
        setScenesTool(Scene::Pen_DrawStraightLine);
    }
    else if (button == mPenSetWgt->ui->toolButtonPen_Points)
    {
        setScenesTool(Scene::Pen_DrawPoints);
    }
}

void PenWindow::updateUI()
{
    mPenSetWgt->ui->spinBoxPenWidth->setValue(mRasterScene->toolPen().width());
    mPenSetWgt->ui->toolButtonPenColor->setIcon(CommonFunc::generateColorIcon(mRasterScene->toolPen().color()));

    Scene::Tool tool = mRasterScene->tool();
    if (tool == Scene::Pen_DrawStraightLine)
        mPenSetWgt->ui->toolButtonPen_StraightLines->setChecked(true);
    else if (tool == Scene::Pen_DrawPoints)
        mPenSetWgt->ui->toolButtonPen_Points->setChecked(true);
}

void PenWindow::setScenesToolPen(const QPen &pen)
{
    mRasterScene->setToolPen(pen);
    mOpenGLScene->setToolPen(pen);
}

void PenWindow::setScenesTool(int tool)
{
    mRasterScene->setTool((Scene::Tool)tool);
    mOpenGLScene->setTool((Scene::Tool)tool);
}















