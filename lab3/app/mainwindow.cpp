#include "./mainwindow.h"
#include "./ui_mainwindow.h"

#include <string.h>

#include <QHeaderView>
#include <QFileDialog>
#include <QMessageBox>
#include <entrypoint.h>
#include <businesslogic.h>
#include <QtMinMax>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    context = new AppContext{};
}

MainWindow::~MainWindow()
{
    performOperation(context, NULL, CleanUp);
    delete context;
    delete ui;
}