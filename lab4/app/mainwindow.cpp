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
    renderingState = new QState(machine);

    QGridLayout* layout = new QGridLayout;
    layout->addWidget(&renderer);
    // renderer.setParent(ui->widget_2);
    ui->renderArea->setLayout(layout);

    ui->stepSlider->setMinimum(100);
    ui->stepSlider->setMaximum(200);
    ui->stepSlider->setSingleStep(1);
    ui->maxSpinBox->setValue(1);

    machine->setInitialState(idleState);

    idleState->assignProperty(ui->loadDataButton, "text", "Load Data");
    idleState->assignProperty(ui->configureRenderUI, "visible", false);
    idleState->assignProperty(&renderer, "visible", false);
    idleState->setObjectName("Idle");

    configureRenderState->assignProperty(ui->configureRenderUI, "visible", true);
    configureRenderState->assignProperty(&renderer, "visible", false);
    configureRenderState->setObjectName("configureRender");

    renderingState->assignProperty(ui->configureRenderUI, "visible", true);
    renderingState->assignProperty(&renderer, "visible", true);
    renderingState->setObjectName("render");

    machine->start();

    connect(this, &MainWindow::fileOpenFailed, this, &MainWindow::onFileOpenFailed);
    connect(this, &MainWindow::fileOpenSucceed, this, &MainWindow::onFileOpenSucceed);
    connect(ui->minSpinBox, &QSpinBox::valueChanged, this, &MainWindow::on_spinboxes_valueChanged);
    connect(ui->maxSpinBox, &QSpinBox::valueChanged, this, &MainWindow::on_spinboxes_valueChanged);

    idleState->addTransition(this, &MainWindow::fileOpenSucceed, configureRenderState);

    configureRenderState->addTransition(this, &MainWindow::fileOpenFailed, idleState);
    configureRenderState->addTransition(this, &MainWindow::renderSucceed, renderingState);
    renderingState->addTransition(this, &MainWindow::renderSucceed, renderingState);

    renderingState->addTransition(this, &MainWindow::fileOpenFailed, idleState);
    renderingState->addTransition(ui->stepSlider, &QSlider::valueChanged, configureRenderState);
    renderingState->addTransition(ui->maxSpinBox, &QSpinBox::valueChanged, configureRenderState);
    renderingState->addTransition(ui->minSpinBox, &QSpinBox::valueChanged, configureRenderState);

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

    fileinfo = QFileInfo(QfilenamePath);
    if (fileinfo.suffix().isEmpty() || fileinfo.suffix() != "csv") {
        emit fileOpenFailed();
        return;
    }

    emit fileOpenSucceed(fileinfo.fileName());
}

void MainWindow::onFileOpenFailed()
{
    QMessageBox::critical(this, "Error", tr("Bad file"));
}

void MainWindow::onFileOpenSucceed(QString filename)
{
    ui->loadDataButton->setText(filename);
}

void MainWindow::on_stepSlider_valueChanged()
{
    size_t currStep = ui->stepSlider->sliderPosition();
    ui->currStepLabel->setText(QString::number(currStep));
}

void MainWindow::on_spinboxes_valueChanged()
{
    size_t maxValue = (size_t)ui->maxSpinBox->value();
    size_t minValue = (size_t)ui->minSpinBox->value();
    qDebug() << "spinboxes valueChanged: " << minValue << ' ' << maxValue;

    ui->minSpinBox->setMaximum(qMax<int, int>(maxValue - 1, 0));

    if(maxValue < minValue)
        return;
}

void MainWindow::on_renderButton_clicked()
{
    double maxValue = (double)ui->maxSpinBox->value();
    double minValue = (double)ui->minSpinBox->value();

    double step = ui->stepSlider->sliderPosition()/100.0;

    qDebug() << "stepSlider valueChanged: " << step << ' ' << maxValue << ' ' << minValue;
    NormalizationParameters nparams {
        .Min = minValue,
        .Max = maxValue,
        .DxScale = step,
        .DyScale = step
    };

    try
    {
        renderer.UnloadScene();
        renderer.LoadScene(fileinfo.absoluteFilePath().toStdString(), nparams);

    } catch(std::exception& e)
    {
        QMessageBox::critical(nullptr, "Error", e.what());
        return;
    }

    if (!machine->configuration().contains(renderingState))
       emit renderSucceed();
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    NormalizationParameters nparams = renderer.GetNormalizationParameters();
    double scaledStep = STEP*nparams.DxScale;
    qDebug() << "scaledStep: " << scaledStep;

    // renderer.RotateScene(ROTATIONANGLE, ROTATIONANGLE,ROTATIONANGLE);
    // renderer.MoveScene(scaledStep, scaledStep, scaledStep);

    switch (event->key())
    {
        case Qt::Key_J:
            renderer.RotateScene(0, ROTATIONANGLE,0);
            break;

        case Qt::Key_L:
            renderer.RotateScene(0, -ROTATIONANGLE,0);
            break;

        case Qt::Key_K:
            renderer.RotateScene(-ROTATIONANGLE, 0,0);
            break;

        case Qt::Key_I:
            renderer.RotateScene(ROTATIONANGLE, 0,0);
            break;

        case Qt::Key_M:
            renderer.RotateScene(0, 0,ROTATIONANGLE);
            break;

        case Qt::Key_N:
            renderer.RotateScene(0, 0,-ROTATIONANGLE);
            break;

        case Qt::Key_W:
            renderer.MoveScene(0, -scaledStep,0);
            break;

        case Qt::Key_S:
            renderer.MoveScene(0, scaledStep,0);
            break;

        case Qt::Key_D:
            renderer.MoveScene(-scaledStep, 0,0);
            break;

        case Qt::Key_A:
            renderer.MoveScene(scaledStep, 0,0);
            break;

        case Qt::Key_Z:
            renderer.MoveScene(0, 0,scaledStep);
            break;

        case Qt::Key_X:
            renderer.MoveScene(0, 0, -scaledStep);
            break;
    }

    // emit renderSucceed();
}