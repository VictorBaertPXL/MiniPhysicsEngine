#pragma once
#include <vector>
#include "body.h"

class PhysicsWorld {
private:
    std::vector<Body*> bodies; // compositie: de world bezit de bodies

public:
    PhysicsWorld() = default;
    ~PhysicsWorld();

    // Voeg een body toe aan de world
    void addBody(Body* body);

    // Verwijder en delete een body
    void removeBody(Body* body);

    // Simuleer één timestep
    void step(float dt);

    // Getter voor alle bodies (const reference)
    const std::vector<Body*>& getBodies() const;
};
