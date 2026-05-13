#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QButtonGroup>
#include <QPushButton>
#include <QSizePolicy>
#include <logic.h>
// #include "appcontext.h"
// #include <entrypoint.h>
#include "ui_mainwindow.h"

#define HEIGHTSELLS 5
#define WIDTHSELLS  4
#define OPERATORSCOUNT  4

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
    void on_anyCalcButton_clicked(int id);

private:
    char calcSymbols[HEIGHTSELLS][WIDTHSELLS] = {
        {'d','c','%','/'},
        {'7','8','9','*'},
        {'4','5','6','-'},
        {'1','2','3','+'},
        {'p','0','.','='},
    };

    char operators[OPERATORSCOUNT] = {
        '/', '*', '-', '+'
    };

    inline bool isOperator(char c);
    void putSymbol(char c);
    void delSymbol();
    void clearText();
    void inverseText();
    void updateText();

    QString text;
    QButtonGroup* calcButtonGroup;
    FacadeCalculator calc;
    Ui::MainWindow* ui;
};
#endif // MAINWINDOW_H
