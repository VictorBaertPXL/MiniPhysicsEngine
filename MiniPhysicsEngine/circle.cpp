#include "circle.h"

// vraag 3: correct class
// vraag 6: correct inheritance
// vraag 7: correct polymorphism
Circle::Circle(float x, float y, float mass, float radius)
    : Body(x, y, mass), radius(radius)
{}

float Circle::getRadius() const { return radius; }

// vraag 7: correct polymorphism
void Circle::applyForces(float dt) {
    ay += 9.81f; // m/s^2 naar beneden
}
