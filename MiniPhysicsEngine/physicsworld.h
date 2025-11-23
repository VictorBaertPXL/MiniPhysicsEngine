#pragma once
#include <vector>
#include "body.h"

// vraag 3: correct class
// vraag 8: correct base class
// vraag 9: correct object composition
class PhysicsWorld {
private:
    std::vector<Body*> bodies; // compositie: de world bezit de bodies

public:
    PhysicsWorld() = default;
    ~PhysicsWorld();

    void addBody(Body* body);
    void removeBody(Body* body);
    void step(float dt);

    const std::vector<Body*>& getBodies() const;
};
