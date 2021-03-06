#ifndef PENWINDOW_H
#define PENWINDOW_H

#include <QMainWindow>
#include <QPen>
#include <QPushButton>

namespace Ui {
class PenWindow;
}

class View;
class PenSetWidget;
class Scene;
class PenWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PenWindow(QWidget *parent = 0);
    ~PenWindow();

private:
    Ui::PenWindow *ui;

    View *mRasterView;
    Scene *mRasterScene;
    View *mOpenGLView;
    Scene *mOpenGLScene;

    PenSetWidget *mPenSetWgt;

private slots:
    void onPenColor();
    void onPenWidthChanged(int w);
    void onR2O();
    void onO2R();
    void onCleanAll();
    void onPenTypeButtonGroupButtonClicked(QAbstractButton *button);
    void onSaveAs();
    void onBlurRadiusChanged(double value);
    void onMinLineLengthChanged(double value);
    void onConnectPointsMethodChanged(int value);

    void updateUI();

    void setScenesToolPen(const QPen &pen);
    void setScenesTool(int tool);
    void on_actionOpenDialog_triggered();
    void on_actionCleanAll_triggered();
    void on_actionCurveConnect_triggered();
    void on_actionCurveConnectUsePainterPath_triggered();
    void on_actionOpenFramelessDialog_triggered();
    void on_actionOpenGLDialog_triggered();
};


#endif // PENWINDOW_H
