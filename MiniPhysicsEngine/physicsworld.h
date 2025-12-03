#pragma once
#include <vector>
#include "body.h"

class PhysicsWorld {
private:
    std::vector<Body*> bodies; // compositie: de world bezit de bodies

public:
    PhysicsWorld() = default;
    ~PhysicsWorld();

    void addBody(Body* body);
    void removeBody(Body* body);

    // physics step + borders + collisions
    void step(float dt, int windowWidth, int windowHeight);

    // collision helpers
    void handleCollisions();
    void resolveCircleCircle(class Circle* c1, class Circle* c2);
    void resolveBoxBox(class Box* b1, class Box* b2);
    void resolveBoxCircle(class Box* box, class Circle* circle);

    const std::vector<Body*>& getBodies() const;
};
