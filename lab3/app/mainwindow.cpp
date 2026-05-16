#include "./mainwindow.h"
#include "./ui_mainwindow.h"

#include <string.h>
#include <stdexcept>
#include <QHeaderView>
#include <QFileDialog>
#include <QMessageBox>
#include <QtMinMax>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // context = new AppContext{};
    calcButtonGroup = new QButtonGroup {};

    // init buttons
    QSizePolicy policy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QGridLayout* layout = new QGridLayout(ui->calcButtonsWidget);

    int buttonId = 0;
    for (int i = 0; i < HEIGHTSELLS; ++i)
    {
        for (int j = 0; j < WIDTHSELLS; ++j)
        {
            QPushButton* button = new QPushButton { QString(calcSymbols[i][j]) };
            calcButtonGroup->addButton(button, buttonId++);
            button->setSizePolicy(policy);
            layout->addWidget(button, i, j);
        }
    }

    connect(calcButtonGroup, &QButtonGroup::idClicked, this, &MainWindow::on_anyCalcButton_clicked);
}

MainWindow::~MainWindow()
{

    // delete layout;
    delete calcButtonGroup;
    delete ui;
    
}

void MainWindow::on_anyCalcButton_clicked(int id)
{
    char ch = *((char*)calcSymbols + id);

    execButtonOperation(ch);
    // qDebug() << text;
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    QChar key = char(event->key());
    key = key.toLower();
    // qDebug() << char(key);
    execButtonOperation(key.toLatin1());
}

void MainWindow::execButtonOperation(char ch)
{
    if(isdigit(ch) || isOperator(ch) || ch == '.') {
        putSymbol(ch);
    }

    if(ch == 'd') {
        delSymbol();
    }

    if(ch == 'c') {
        clearText();
    }

    if(ch == 'p') {
        inverseText();
    }

    if(ch == '=') {
        try {
            double res = calc.calcExpression(text);
            text = QString::number(res, 'f', CALCRESOLUTION);
            while(text.endsWith('0')) {
                text.removeLast();
            }

            if(text.endsWith('.')) {
                text.removeLast();
            }
            
        } catch (const std::invalid_argument& e) {
            QMessageBox::critical(this, "ERROR", "BAD CALCULATION");
            // text.clear();
        }
    }

    updateText();
}

inline bool MainWindow::isOperator(char c) {
    for (size_t i = 0; i < OPERATORSCOUNT; i++)
        if(operators[i] == c)
            return true;

    return false;
}

inline void MainWindow::putSymbol(char c) {
    text.append(c);
}

inline void MainWindow::delSymbol() {
    text.removeLast();
}

inline void MainWindow::inverseText() {
    if(text[0] == '-'){
        text.removeFirst();
    } else {
        text.insert(0, '-');
    }    
}

inline void MainWindow::updateText() {
    ui->textBrowser->setText(text);
}

inline void MainWindow::clearText() {
    text.clear();
}