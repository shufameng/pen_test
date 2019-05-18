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
#include <QFileDialog>

PenWindow::PenWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PenWindow)
{
    ui->setupUi(this);
    setWindowTitle("Attention: The right side is rendered by OpenGL");

    // views
    mRasterView = new View();
    mRasterView->setScene(mRasterScene = new Scene());

    mRasterView->show();
    mOpenGLView = new View();
    mOpenGLView->setScene(mOpenGLScene = new Scene());

    QHBoxLayout *hlay = new QHBoxLayout(centralWidget());
    //hlay->addWidget(mRasterView);
    //hlay->addWidget(mOpenGLView);

    // PenSetWidget
    mPenSetWgt = new PenSetWidget(this);
    mPenSetWgt->show();
    connect(mPenSetWgt->ui->toolButtonPenColor, SIGNAL(clicked()), this, SLOT(onPenColor()));
    connect(mPenSetWgt->ui->spinBoxPenWidth, SIGNAL(valueChanged(int)), this, SLOT(onPenWidthChanged(int)));
    connect(mPenSetWgt->ui->pushButton_o2r, SIGNAL(clicked()), this, SLOT(onO2R()));
    connect(mPenSetWgt->ui->pushButton_r2o, SIGNAL(clicked()), this, SLOT(onR2O()));
    connect(mPenSetWgt->ui->pushButtonCleanAll, SIGNAL(clicked()), this, SLOT(onCleanAll()));
    connect(mPenSetWgt->ui->pushButtonSaveAs, SIGNAL(clicked()), this, SLOT(onSaveAs()));
    connect(mPenSetWgt->ui->doubleSpinBoxBlurRadius, SIGNAL(valueChanged(double)), this, SLOT(onBlurRadiusChanged(double)));
    connect(mPenSetWgt->ui->doubleSpinBoxMinLineLength, SIGNAL(valueChanged(double)), this, SLOT(onMinLineLengthChanged(double)));
    connect(mPenSetWgt->ui->comboBoxConnectPointsMethod, SIGNAL(activated(int)), this, SLOT(onConnectPointsMethodChanged(int)));

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
        updateUI();
    }
}

void PenWindow::onPenWidthChanged(int w)
{
    QPen p = mRasterScene->toolPen();
    p.setWidth(w);

    setScenesToolPen(p);
    updateUI();
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

void PenWindow::onSaveAs()
{
    QString path = QFileDialog::getSaveFileName(this);
    if (path.isEmpty())
        return;

    mRasterScene->saveAs(path);
}

void PenWindow::onBlurRadiusChanged(double value)
{
    mRasterScene->setBlurRadius((qreal)value);
    mOpenGLScene->setBlurRadius((qreal)value);
}

void PenWindow::onMinLineLengthChanged(double value)
{
    mRasterScene->setMinLineLength(value);
    mOpenGLScene->setMinLineLength(value);
}

void PenWindow::onConnectPointsMethodChanged(int value)
{
    mRasterScene->setConnectPointsMethod((Scene::ConnectPointsMethod)value);
    mOpenGLScene->setConnectPointsMethod((Scene::ConnectPointsMethod)value);
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

    mPenSetWgt->ui->doubleSpinBoxBlurRadius->setValue(mRasterScene->blurRadius());
    mPenSetWgt->ui->doubleSpinBoxMinLineLength->setValue(mRasterScene->minLineLength());

    Scene::ConnectPointsMethod method = mRasterScene->connectPointsMethod();
    mPenSetWgt->ui->comboBoxConnectPointsMethod->setCurrentIndex((int)method);
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

void PenWindow::on_actionOpenDialog_triggered()
{
    View *v = new View;
    v->setWindowFlags(Qt::FramelessWindowHint | Qt::ToolTip);
    v->setScene(mRasterScene);
    v->resize(600, 400);
    v->show();
}
