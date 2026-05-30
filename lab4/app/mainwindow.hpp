#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qfileinfo.h>
#include <QStateMachine>
#include <QMainWindow>

#include "core/RendererFacade.h"
#include "surfacedrawer/QtDrawerWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;


public slots:
    void on_loadDataButton_clicked();
    void onFileOpenFailed();
    void onFileOpenSucceed(QString filename);
    void on_stepSlider_valueChanged();
    void on_spinboxes_valueChanged();
    void on_renderButton_clicked();

signals:
    void fileOpenFinished();
    void fileOpenSucceed(QString filename);
    void fileOpenFailed();
    void renderSucceed();

private:

    void keyPressEvent(QKeyEvent* event);

    QFileInfo fileinfo;
    QState* idleState;
    QState* configureRenderState;
    QState* renderingState;
    QStateMachine* machine;
    Ui::MainWindow* ui;
    QtDrawerWidget renderer;
};
#endif // MAINWINDOW_H
