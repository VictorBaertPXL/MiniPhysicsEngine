#include "body.h"

Body::Body(float x, float y, float mass)
    : mass(mass), x(x), y(y), vx(0), vy(0), ax(0), ay(0)
{}

// Getters
float Body::getX() const { return x; }
float Body::getY() const { return y; }
float Body::getVX() const { return vx; }
float Body::getVY() const { return vy; }
float Body::getMass() const { return mass; }

// Default applyForces: geen extra krachten
void Body::applyForces(float dt) {
    // kan overschreven worden door Box/Circle
}

// Integratie met Euler methode
void Body::integrate(float dt) {
    // update snelheid
    vx += ax * dt;
    vy += ay * dt;

    // update positie
    x += vx * dt;
    y += vy * dt;

    // reset acceleratie
    ax = 0;
    ay = 0;
}
