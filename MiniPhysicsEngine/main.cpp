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

    // voorbeeld bodies
    world.addBody(new Box(50.0f, 150.0f, 50.0f, 60.0f, 60.0f));   // box (x,y) bottom-left
    world.addBody(new Box(220.0f, 200.0f, 80.0f, 80.0f, 80.0f));

    world.addBody(new Circle(120.0f, 80.0f, 30.0f, 20.0f)); // circle at (x,y) center
    world.addBody(new Circle(180.0f, 40.0f, 20.0f, 14.0f));

    MainWindow w(&world);
    w.resize(800, 600);
    w.show();

    return app.exec();
}
