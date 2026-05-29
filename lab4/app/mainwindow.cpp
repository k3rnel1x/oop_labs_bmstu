#include "mainwindow.hpp"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    renderer(std::make_unique<CsvFileReader>())
{
    ui->setupUi(this);
    machine = new QStateMachine(this);
    idleState = new QState(machine);
    configureRenderState = new QState(machine);

    renderer.setParent(ui->renderArea);

    machine->setInitialState(idleState);

    idleState->assignProperty(ui->loadDataButton, "text", "Load Data");
    idleState->assignProperty(ui->configureRenderUI, "visible", false);
    idleState->assignProperty(&renderer, "visible", false);
    idleState->addTransition(this, &MainWindow::fileOpenSucceed, configureRenderState);
    idleState->setObjectName("Idle");

    configureRenderState->assignProperty(ui->loadDataButton, "text", "Not Load Data");
    configureRenderState->assignProperty(ui->configureRenderUI, "visible", true);
    configureRenderState->assignProperty(&renderer, "visible", true);
    configureRenderState->addTransition(this, &MainWindow::fileOpenFinished, idleState);
    configureRenderState->setObjectName("configureRender");

    machine->start();

    connect(this, &MainWindow::fileOpenFailed, this, &MainWindow::onFileOpenFailed);
}

MainWindow::~MainWindow()
{
    delete idleState;
    delete configureRenderState;
    delete machine;
    delete ui;
}

void MainWindow::on_loadDataButton_clicked()
{
    QString QfilenamePath = QFileDialog::getOpenFileName(
        this,
        tr("Open data"),
        "~/",
        tr("Table (*.csv)")
    );

    if(QfilenamePath.isEmpty()){
        emit fileOpenFinished();
        return;
    }

    QFileInfo file(QfilenamePath);
    if (file.suffix().isEmpty() || file.suffix() != "csv") {
        emit fileOpenFailed();
        return;
    }

    ui->loadDataButton->setText(file.fileName());
}

void MainWindow::onFileOpenFailed()
{
    QMessageBox::critical(this, "Error", tr("Bad file"));
}

