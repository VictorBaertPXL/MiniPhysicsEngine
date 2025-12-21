#include "box.h"

Box::Box(float x, float y, float mass, const float& width, const float& height)
    : Body(x, y, mass),
    width(width),
    height(height)
{}

float Box::getHeight() const {
    return height;
}

void Box::applyForces(float dt) {
    ay += 100.0f;
}
