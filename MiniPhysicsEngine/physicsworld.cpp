#include "physicsworld.h"
#include <algorithm>

PhysicsWorld::~PhysicsWorld() {
    for (Body* body : bodies) {
        delete body;
    }
    bodies.clear();
}

void PhysicsWorld::addBody(Body* body) {
    bodies.push_back(body);
}

void PhysicsWorld::removeBody(Body* body) {
    auto it = std::find(bodies.begin(), bodies.end(), body);
    if (it != bodies.end()) {
        delete *it;
        bodies.erase(it);
    }
}

// vraag 7: correct polymorphism
void PhysicsWorld::step(float dt, int windowWidth, int windowHeight) {
    for (Body* body : bodies) {
        body->applyForces(dt);
    }
    for (Body* body : bodies) {
        body->integrate(dt, windowWidth, windowHeight);
    }
}

const std::vector<Body*>& PhysicsWorld::getBodies() const {
    return bodies;
}
