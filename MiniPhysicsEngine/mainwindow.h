#pragma once

#include <QMainWindow>
#include "physicsworld.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    PhysicsWorld* world; // pointer naar physics world
    QTimer* timer;       // timer voor de simulatie

public:
    explicit MainWindow(PhysicsWorld* w, QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent* event) override; // render de physics
};
