#include "box.h"

// vraag 3: correct class
// vraag 6: correct inheritance
// vraag 7: correct polymorphism
Box::Box(float x, float y, float mass, float width, float height)
    : Body(x, y, mass), width(width), height(height)
{}

float Box::getWidth() const { return width; }
float Box::getHeight() const { return height; }

// vraag 7: correct polymorphism
void Box::applyForces(float dt) {
    ay += 9.81f; // m/s^2 naar beneden
}
