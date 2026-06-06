//
// Created by k3rnel1x on 05.06.2026.
//

#ifndef LAB5_FLOOR_H
#define LAB5_FLOOR_H
#include <QWidget>
#include <QApplication>
#include <QScreen>
#include <QLabel>
#include <QPushButton>
#include <QString>

class Floor : public QWidget {
    Q_OBJECT

class FloorButton : public QPushButton {
public:
    explicit FloorButton(int floor, int x, int y);
    void closeEvent(QCloseEvent *event) override;
    void moveEvent(QMoveEvent *event) override;


private:
    int x, y;
};

public:
    explicit Floor(int floor, int step, int gapsY, int gapsX);
    QPushButton* getButton() { return button; };

    void closeEvent(QCloseEvent *event) override;
    void moveEvent(QMoveEvent *event) override;

private:
    FloorButton* button;
    int x, y;
};


#endif //LAB5_FLOOR_H
