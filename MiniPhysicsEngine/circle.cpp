#include "circle.h"

Circle::Circle(float x, float y, float mass, const float& radius)
    : Body(x, y, mass),
    radius(radius)
{}

void Circle::applyForces(float dt) {
    ay += 100.0f;
}
