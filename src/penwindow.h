#ifndef PENWINDOW_H
#define PENWINDOW_H

#include <QMainWindow>
#include <QPen>

namespace Ui {
class PenWindow;
}

class View;
class PenSetWidget;
class PenWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PenWindow(QWidget *parent = 0);
    ~PenWindow();

private:
    Ui::PenWindow *ui;

    View *mRasterView;
    View *mOpenGLView;

    PenSetWidget *mPenSetWgt;

private slots:
    void onPenColor();
    void onPenWidthChanged(int w);
    void onR2O();
    void onO2R();
    void onCleanAll();

    QPen getPen();
    void setPen(const QPen &p);

    void updateUI();
};

#endif // PENWINDOW_H
