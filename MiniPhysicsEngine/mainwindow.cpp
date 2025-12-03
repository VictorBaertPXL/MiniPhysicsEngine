#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include "box.h"
#include "circle.h"

// vraag 3: correct class
// vraag 8: correct base class
MainWindow::MainWindow(PhysicsWorld* w, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , world(w)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this]() {
        const int windowWidth = this->width();
        const int windowHeight = this->height();

        // physics step (forces, integrate with borders, collisions)
        world->step(0.016f, windowWidth, windowHeight);

        update();
    });
    timer->start(16);
}

MainWindow::~MainWindow() {
    delete ui;
}

// vraag 3: correct class
// vraag 7: correct polymorphism
void MainWindow::paintEvent(QPaintEvent* /*event*/) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    const auto& bodies = world->getBodies();
    for (Body* body : bodies) {
        if (Box* box = dynamic_cast<Box*>(body)) {
            painter.setBrush(Qt::blue);
            // drawRect expects left-top: convert from left-bottom (box->getY() is bottom)
            painter.drawRect(box->getX(), box->getY() - box->getHeight(),
                             box->getWidth(), box->getHeight());
        }
        else if (Circle* circle = dynamic_cast<Circle*>(body)) {
            painter.setBrush(Qt::red);
            painter.drawEllipse(circle->getX() - circle->getRadius(),
                                circle->getY() - circle->getRadius(),
                                circle->getRadius()*2,
                                circle->getRadius()*2);
        }
    }
}

// Drag & Drop
void MainWindow::mousePressEvent(QMouseEvent* event) {
    const auto& bodies = world->getBodies();
    for (Body* body : bodies) {
        if (Box* box = dynamic_cast<Box*>(body)) {
            QRect rect(box->getX(), box->getY() - box->getHeight(),
                       box->getWidth(), box->getHeight());
            if (rect.contains(event->pos())) {
                dragBody = body;
                dragOffset = event->pos() - QPoint(box->getX(), box->getY() - box->getHeight());
                dragBody->setVX(0);
                dragBody->setVY(0);
                break;
            }
        }
        else if (Circle* circle = dynamic_cast<Circle*>(body)) {
            QRect rect(circle->getX() - circle->getRadius(),
                       circle->getY() - circle->getRadius(),
                       circle->getRadius()*2, circle->getRadius()*2);
            if (rect.contains(event->pos())) {
                dragBody = body;
                dragOffset = event->pos() - QPoint(circle->getX() - circle->getRadius(),
                                                   circle->getY() - circle->getRadius());
                dragBody->setVX(0);
                dragBody->setVY(0);
                break;
            }
        }
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent* event) {
    if (!dragBody) return;

    int newX = event->pos().x() - dragOffset.x();
    int newY = event->pos().y() - dragOffset.y();

    if (Box* box = dynamic_cast<Box*>(dragBody)) {
        box->setX(newX);
        box->setY(newY + box->getHeight()); // y is bottom
    }
    else if (Circle* circle = dynamic_cast<Circle*>(dragBody)) {
        circle->setX(newX + circle->getRadius());
        circle->setY(newY + circle->getRadius());
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent* /*event*/) {
    if (dragBody) {
        dragBody->setVX(0);
        dragBody->setVY(0);
        dragBody = nullptr;
    }
}
