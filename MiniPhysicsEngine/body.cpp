#include "body.h"

// vraag 3: correct class
// vraag 4: correct abstraction
// vraag 5: correct encapsulation
Body::Body(float x, float y, float mass)
    : mass(mass), x(x), y(y), vx(0), vy(0), ax(0), ay(0)
{}

// Getters
float Body::getX() const { return x; }
float Body::getY() const { return y; }
float Body::getVX() const { return vx; }
float Body::getVY() const { return vy; }
float Body::getMass() const { return mass; }

// vraag 11: correct virtual function
void Body::applyForces(float dt) {
    // kan overschreven worden door Box/Circle
}

// Integratie met Euler methode + border detectie
void Body::integrate(float dt, float windowWidth, float windowHeight) {
    // update snelheid
    vx += ax * dt;
    vy += ay * dt;

    // update positie
    x += vx * dt;
    y += vy * dt;

    // reset acceleratie
    ax = 0;
    ay = 0;

    // Borders: botsing met window
    if (x < 0) {
        x = 0;
        vx = 0;
    } else if (x > windowWidth) {
        x = windowWidth;
        vx = 0;
    }

    if (y < 0) {
        y = 0;
        vy = 0;
    } else if (y > windowHeight) {
        y = windowHeight;
        vy = 0;
    }
}
