#include "mainwindow.h"
#include <QPainter>

MainWindow::MainWindow(PhysicsWorld* w, QWidget *parent)
    : QMainWindow(parent),
    world(w)
{
    setMouseTracking(true);
}

MainWindow::~MainWindow() {}

void MainWindow::paintEvent(QPaintEvent*)
{
    if (!world) return;

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    const auto& bodies = world->getBodies();

    // const reference added
    for (Body* const& body : bodies) {
        if (Circle* c = dynamic_cast<Circle*>(body)) {
            p.setBrush(Qt::blue);
            p.drawEllipse(
                QPointF(c->getX(), c->getY()),
                c->getRadius(),
                c->getRadius()
                );
        }
        else if (Box* b = dynamic_cast<Box*>(body)) {
            p.setBrush(Qt::red);
            p.drawRect(
                b->getX(),
                b->getY() - b->getHeight(),
                b->getWidth(),
                b->getHeight()
                );
        }
    }
}

void MainWindow::mousePressEvent(QMouseEvent* event)
{
    if (!world) return;

    dragBody = nullptr;

    const auto& bodies = world->getBodies();
    const float mx = event->pos().x();
    const float my = event->pos().y();

    // const reference added
    for (Body* const& body : bodies) {
        if (Circle* c = dynamic_cast<Circle*>(body)) {
            float dx = mx - c->getX();
            float dy = my - c->getY();
            if (dx*dx + dy*dy <= c->getRadius()*c->getRadius()) {
                dragBody = body;
                return;
            }
        }

        if (Box* b = dynamic_cast<Box*>(body)) {
            if (mx >= b->getX() &&
                mx <= b->getX() + b->getWidth() &&
                my <= b->getY() &&
                my >= b->getY() - b->getHeight()) {
                dragBody = body;
                return;
            }
        }
    }

    QMainWindow::mousePressEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
    if (dragBody) {
        dragBody->setX(event->pos().x());
        dragBody->setY(event->pos().y());
        dragBody->setVX(0.0f);
        dragBody->setVY(0.0f);
        update();
        return;
    }

    QMainWindow::mouseMoveEvent(event);
}

void MainWindow::mouseReleaseEvent(QMouseEvent* event)
{
    dragBody = nullptr;
    QMainWindow::mouseReleaseEvent(event);
}
