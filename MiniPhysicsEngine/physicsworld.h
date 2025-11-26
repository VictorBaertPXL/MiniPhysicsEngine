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

    // aangepast: stap met borders
    void step(float dt, int windowWidth, int windowHeight);

    const std::vector<Body*>& getBodies() const;
};
