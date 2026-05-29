#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

    QState* idleState;
    QState* configureRenderState;
public slots:
    void on_loadDataButton_clicked();
    void onFileOpenFailed();
    // void on_renderButton_clicked();

signals:
    void fileOpenFinished();
    void fileOpenSucceed();
    void fileOpenFailed();

private:
    QStateMachine* machine;
    Ui::MainWindow* ui;
    QtDrawerWidget renderer;
};
#endif // MAINWINDOW_H
