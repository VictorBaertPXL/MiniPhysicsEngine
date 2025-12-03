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
    // default gravity pointing down in pixels/s^2 (user used ~100 in your code)
    ay += 100.0f; // you chose large value earlier — keep it consistent
}
