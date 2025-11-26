#pragma once

#include <QMainWindow>
#include <QMouseEvent>
#include <QPointF>
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

    Body* selectedBody = nullptr;  // object dat we slepen
    QPointF dragOffset;            // offset tussen muis en object

public:
    explicit MainWindow(PhysicsWorld* w, QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent* event) override;

    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
};
