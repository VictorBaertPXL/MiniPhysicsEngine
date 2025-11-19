#include "circle.h"

Circle::Circle(float x, float y, float mass, float radius)
    : Body(x, y, mass), radius(radius)
{}

float Circle::getRadius() const { return radius; }

void Circle::applyForces(float dt) {
    // Hier kan je krachten toevoegen die specifiek zijn voor Circle
    ay += 9.81f; // m/s^2 naar beneden
}
