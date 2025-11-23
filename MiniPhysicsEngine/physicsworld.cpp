#include "physicsworld.h"
#include <algorithm>

// vraag 3: correct class
// vraag 9: correct object composition
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

void PhysicsWorld::step(float dt) {
    for (Body* body : bodies) {
        body->applyForces(dt);  // vraag 7: correct polymorphism
    }
    for (Body* body : bodies) {
        body->integrate(dt);
    }
}

const std::vector<Body*>& PhysicsWorld::getBodies() const {
    return bodies;
}
