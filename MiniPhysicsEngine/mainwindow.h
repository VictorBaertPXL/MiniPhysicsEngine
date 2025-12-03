#pragma once

#include <QMainWindow>
#include <QMouseEvent>
#include <QPoint>
#include <QTimer>
#include "physicsworld.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// vraag 3: correct class
// vraag 8: correct base class
class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    PhysicsWorld* world; // pointer naar physics world
    QTimer* timer;       // timer voor de simulatie

    // Drag & Drop
    Body* dragBody = nullptr;
    QPoint dragOffset;

public:
    explicit MainWindow(PhysicsWorld* w, QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
};
