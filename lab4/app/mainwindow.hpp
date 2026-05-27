#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QStateMachine>
#include <QMainWindow>

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

private:
    QStateMachine machine;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
