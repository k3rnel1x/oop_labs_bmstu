#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "appcontext.h"
#include <entrypoint.h>
#include "ui_mainwindow.h"

#define DEFAULTLOADTEXT "Load Data"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:

private slots:

private:
    AppContext* context;
    Ui::MainWindow* ui;
};
#endif // MAINWINDOW_H
