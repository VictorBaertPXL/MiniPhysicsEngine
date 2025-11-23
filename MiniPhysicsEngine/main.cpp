#include <QApplication>
#include "mainwindow.h"
#include "physicsworld.h"
#include "box.h"
#include "circle.h"

// vraag 3: correct class
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    PhysicsWorld world;

    // vraag 3: correct class
    world.addBody(new Box(1.0f, 50.0f, 50.0f, 30.0f, 30.0f));
    world.addBody(new Box(2.0f, 150.0f, 50.0f, 50.0f, 50.0f));

    // vraag 3: correct class
    world.addBody(new Circle(1.0f, 100.0f, 100.0f, 20.0f));
    world.addBody(new Circle(1.5f, 200.0f, 150.0f, 30.0f));

    MainWindow w(&world);
    w.show();

    return app.exec();
}
