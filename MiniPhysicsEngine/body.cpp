#include "body.h"
#include "box.h"
#include "circle.h"
#include <algorithm>

// Constructor
Body::Body(float x, float y, float mass)
    : mass(mass), x(x), y(y), vx(0), vy(0), ax(0), ay(0),
    restitution(0.6f), friction(0.1f)
{}

// Getters
float Body::getX() const { return x; }
float Body::getY() const { return y; }
float Body::getVX() const { return vx; }
float Body::getVY() const { return vy; }
float Body::getMass() const { return mass; }

// Setters
void Body::setX(float newX) { x = newX; }
void Body::setY(float newY) { y = newY; }
void Body::setVX(float newVX) { vx = newVX; }
void Body::setVY(float newVY) { vy = newVY; }

float Body::getRestitution() const { return restitution; }
float Body::getFriction() const { return friction; }
void Body::setRestitution(float r) { restitution = r; }
void Body::setFriction(float f) { friction = f; }

// Forces (virtual)
void Body::applyForces(float dt) {
    // default: niets (afgeleiden zetten zwaartekracht)
}

// Integratie met Euler methode + border detectie op echte omtrek
void Body::integrate(float dt, float windowWidth, float windowHeight) {
    // Update snelheid
    vx += ax * dt;
    vy += ay * dt;

    // Update positie
    x += vx * dt;
    y += vy * dt;

    // Reset acceleratie
    ax = 0;
    ay = 0;

    // Border botsingen afhankelijk van type object
    if (Box* box = dynamic_cast<Box*>(this)) {
        // linkeronderhoek (x, y) is linksonder
        if (box->getX() < 0) {
            x = 0;
            vx = 0;
        }
        if (box->getY() < box->getHeight()) {
            y = box->getHeight();
            vy = 0;
        }
        if (box->getX() + box->getWidth() > windowWidth) {
            x = windowWidth - box->getWidth();
            vx = 0;
        }
        if (box->getY() > windowHeight) {
            y = windowHeight;
            vy = 0;
        }
    }
    else if (Circle* circle = dynamic_cast<Circle*>(this)) {
        // (x, y) is middelpunt
        if (x - circle->getRadius() < 0) {
            x = circle->getRadius();
            vx = 0;
        }
        if (y - circle->getRadius() < 0) {
            y = circle->getRadius();
            vy = 0;
        }
        if (x + circle->getRadius() > windowWidth) {
            x = windowWidth - circle->getRadius();
            vx = 0;
        }
        if (y + circle->getRadius() > windowHeight) {
            y = windowHeight - circle->getRadius();
            vy = 0;
        }
    }
}
