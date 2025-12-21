#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include "physicsworld.h"
#include "body.h"
#include "circle.h"
#include "box.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    PhysicsWorld* world = nullptr;
    Body* dragBody = nullptr;

public:
    explicit MainWindow(PhysicsWorld* w, QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent*) override;
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void mouseReleaseEvent(QMouseEvent*) override;
};

#endif // MAINWINDOW_H
