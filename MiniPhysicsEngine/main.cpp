#include <QApplication>
#include <QTimer>
#include <QDebug>
#include <thread>
#include <atomic>
#include <chrono>

#include "physicsworld.h"
#include "circle.h"
#include "box.h"
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    PhysicsWorld world;

    auto* c1 = new Circle(200, 100, 1.0f, 30.0f);
    c1->setName("BlueBall");
    world.addBody(c1);

    auto* c2 = new Circle(300, 50, 1.0f, 20.0f);
    c2->setName("SmallBall");
    world.addBody(c2);

    auto* b1 = new Box(400, 200, 1.0f, 60.0f, 40.0f);
    b1->setName("RedBox");
    world.addBody(b1);


    auto printBodyName = [](Body* b) {
        qDebug() << "Body name:" << b->getName().c_str();
    };

    for (Body* b : world.getBodies()) {
        printBodyName(b);
    }


    std::atomic<bool> running(true);

    std::thread monitorThread([&]() {
        while (running.load()) {
            int count = world.getBodies().size();
            qDebug() << "[Thread] Number of bodies:" << count;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });


    MainWindow w(&world);
    w.setFixedSize(800, 600);
    w.show();

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&]() {
        world.step(0.016f, w.width(), w.height());
        w.update();
    });
    timer.start(16);

    int result = app.exec();

    // Stop thread netjes
    running.store(false);
    if (monitorThread.joinable())
        monitorThread.join();

    return result;
}
