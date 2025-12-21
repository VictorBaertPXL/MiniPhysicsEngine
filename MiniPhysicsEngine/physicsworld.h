#ifndef PHYSICSWORLD_H
#define PHYSICSWORLD_H

#include <vector>
#include "body.h"

class Circle;
class Box;

class PhysicsWorld {
private:
    std::vector<Body*> bodies;

    bool enableGravity = true;
    bool enableCollisions = true;

public:
    PhysicsWorld() = default;
    ~PhysicsWorld();

    void addBody(Body* body);
    void removeBody(Body* body);

    void step(float dt, int windowWidth, int windowHeight);

    void handleCollisions();
    void resolveCircleCircle(Circle* c1, Circle* c2);
    void resolveBoxBox(Box* b1, Box* b2);
    void resolveBoxCircle(Box* box, Circle* circle);

    const std::vector<Body*>& getBodies() const;

    void setEnableGravity(bool v) { enableGravity = v; }
    void setEnableCollisions(bool v) { enableCollisions = v; }

    bool getEnableGravity() const { return enableGravity; }
    bool getEnableCollisions() const { return enableCollisions; }

    template<typename T>
    T clamp(const T& value, const T& min, const T& max) {
        if (value < min) return min;
        if (value > max) return max;
        return value;
    }
};

#endif // PHYSICSWORLD_H
