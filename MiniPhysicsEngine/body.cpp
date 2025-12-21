#include "body.h"
#include "box.h"
#include "circle.h"
#include <algorithm>

Body::Body(float x, float y, float mass)
    : x(x), y(y),
    vx(0.0f), vy(0.0f),
    ax(0.0f), ay(0.0f),
    mass(mass),
    isStatic(false),
    isCollidable(true),
    name("Unnamed")
{}

Body::Body(const Body& other)
    : x(other.x), y(other.y),
    vx(other.vx), vy(other.vy),
    ax(other.ax), ay(other.ay),
    mass(other.mass),
    isStatic(other.isStatic),
    isCollidable(other.isCollidable),
    name(other.name)
{}

Body::~Body() {}

float Body::getX() const { return x; }
float Body::getY() const { return y; }
float Body::getVX() const { return vx; }
float Body::getVY() const { return vy; }
float Body::getMass() const { return mass; }

bool Body::getIsStatic() const { return isStatic; }
bool Body::getIsCollidable() const { return isCollidable; }

void Body::setIsStatic(bool v) { isStatic = v; }
void Body::setIsCollidable(bool v) { isCollidable = v; }

void Body::setX(float v) { x = v; }
void Body::setY(float v) { y = v; }
void Body::setVX(float v) { vx = v; }
void Body::setVY(float v) { vy = v; }

void Body::setName(const std::string& n) { name = n; }
const std::string& Body::getName() const { return name; }

void Body::integrate(float dt, float windowWidth, float windowHeight) {
    if (isStatic) return;

    vx += ax * dt;
    vy += ay * dt;

    x += vx * dt;
    y += vy * dt;

    ax = 0.0f;
    ay = 0.0f;

    if (Box* box = dynamic_cast<Box*>(this)) {
        if (x < 0.0f) { x = 0.0f; vx = 0.0f; }
        if (y < box->getHeight()) { y = box->getHeight(); vy = 0.0f; }
        if (x + box->getWidth() > windowWidth) { x = windowWidth - box->getWidth(); vx = 0.0f; }
        if (y > windowHeight) { y = windowHeight; vy = 0.0f; }
    }
    else if (Circle* c = dynamic_cast<Circle*>(this)) {
        if (x - c->getRadius() < 0.0f) { x = c->getRadius(); vx = 0.0f; }
        if (y - c->getRadius() < 0.0f) { y = c->getRadius(); vy = 0.0f; }
        if (x + c->getRadius() > windowWidth) { x = windowWidth - c->getRadius(); vx = 0.0f; }
        if (y + c->getRadius() > windowHeight) { y = windowHeight - c->getRadius(); vy = 0.0f; }
    }
}
