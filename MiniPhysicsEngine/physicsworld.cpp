#include "physicsworld.h"
#include <algorithm>

PhysicsWorld::~PhysicsWorld() {
    // Zorg dat alle dynamically allocated bodies worden opgeruimd
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
        delete *it;          // free memory
        bodies.erase(it);    // verwijder uit vector
    }
}

void PhysicsWorld::step(float dt) {
    for (Body* body : bodies) {
        body->applyForces(dt);  // polymorphic call
    }
    for (Body* body : bodies) {
        body->integrate(dt);    // algemene integratie
    }
}

const std::vector<Body*>& PhysicsWorld::getBodies() const {
    return bodies;
}
