#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QTimer>
#include "box.h"
#include "circle.h"

MainWindow::MainWindow(PhysicsWorld* w, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , world(w)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this]() {
        world->step(0.016f); // dt ~16ms (60 FPS)
        update();
    });
    timer->start(16); // ~60 Hz
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent* /*event*/)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    const auto& bodies = world->getBodies();
    for (Body* body : bodies) {
        if (Box* box = dynamic_cast<Box*>(body)) {
            painter.setBrush(Qt::blue);
            painter.drawRect(box->getX(), box->getY(), box->getWidth(), box->getHeight());
        } else if (Circle* circle = dynamic_cast<Circle*>(body)) {
            painter.setBrush(Qt::red);
            painter.drawEllipse(circle->getX() - circle->getRadius(),
                                circle->getY() - circle->getRadius(),
                                circle->getRadius()*2,
                                circle->getRadius()*2);
        }
    }
}

// ---------------- Mouse Drag & Drop ----------------

void MainWindow::mousePressEvent(QMouseEvent* event)
{
    const auto& bodies = world->getBodies();
    for (Body* body : bodies) {
        if (Box* box = dynamic_cast<Box*>(body)) {
            QRectF rect(box->getX(), box->getY(), box->getWidth(), box->getHeight());
            if (rect.contains(event->pos())) {
                selectedBody = box;
                dragOffset = event->pos() - QPointF(box->getX(), box->getY());
                break;
            }
        } else if (Circle* circle = dynamic_cast<Circle*>(body)) {
            QPointF center(circle->getX(), circle->getY());
            if (QLineF(center, event->pos()).length() <= circle->getRadius()) {
                selectedBody = circle;
                dragOffset = event->pos() - center;
                break;
            }
        }
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
    if (selectedBody) {
        selectedBody->setPosition(event->pos().x() - dragOffset.x(),
                                  event->pos().y() - dragOffset.y());
        update(); // herteken
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent* /*event*/)
{
    if (selectedBody) {
        selectedBody->setVelocity(0, 0); // stop direct
    }
    selectedBody = nullptr; // loslaten
}
