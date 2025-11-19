#include "box.h"

Box::Box(float x, float y, float mass, float width, float height)
    : Body(x, y, mass), width(width), height(height)
{}

float Box::getWidth() const { return width; }
float Box::getHeight() const { return height; }

void Box::applyForces(float dt) {
    // Hier kan je krachten toevoegen die specifiek zijn voor Box
    // Bijvoorbeeld zwaartekracht
    ay += 9.81f; // m/s^2 naar beneden
}
