#include "physicsworld.h"
#include "box.h"
#include "circle.h"
#include <algorithm>
#include <cmath>
#include <fstream>   // file I/O
#include <iostream>  // optional debug output

PhysicsWorld::~PhysicsWorld() {
    for (Body* body : bodies) {
        delete body;
    }
    bodies.clear();
}

void PhysicsWorld::addBody(Body* body) {
    bodies.push_back(body);
}

void PhysicsWorld::removeBody(Body* body) {
    auto it = std::find(bodies.begin(), bodies.end(), body);
    if (it != bodies.end()) {
        delete *it;
        bodies.erase(it);
    }
}

void PhysicsWorld::step(float dt, int windowWidth, int windowHeight) {
    if (enableGravity) {
        for (Body* body : bodies) {
            body->applyForces(dt);
        }
    }

    const bool limitVelocity = true;

    for (Body* body : bodies) {
        if (limitVelocity) {
            float vx = clamp(body->getVX(), -500.0f, 500.0f);
            float vy = clamp(body->getVY(), -500.0f, 500.0f);
            body->setVX(vx);
            body->setVY(vy);
        }

        body->integrate(dt, windowWidth, windowHeight);
    }

    if (enableCollisions) {
        handleCollisions();
    }
}

void PhysicsWorld::handleCollisions() {
    const size_t n = bodies.size();

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = i + 1; j < n; ++j) {
            Body* A = bodies[i];
            Body* B = bodies[j];

            if (!A->getIsCollidable() || !B->getIsCollidable())
                continue;

            if (Circle* c1 = dynamic_cast<Circle*>(A)) {
                if (Circle* c2 = dynamic_cast<Circle*>(B)) {
                    resolveCircleCircle(c1, c2);
                    continue;
                }
            }

            if (Box* b1 = dynamic_cast<Box*>(A)) {
                if (Box* b2 = dynamic_cast<Box*>(B)) {
                    resolveBoxBox(b1, b2);
                    continue;
                }
            }

            Box* box = dynamic_cast<Box*>(A);
            Circle* circle = dynamic_cast<Circle*>(B);

            if (!box) {
                box = dynamic_cast<Box*>(B);
                circle = dynamic_cast<Circle*>(A);
            }

            if (box && circle) {
                resolveBoxCircle(box, circle);
            }
        }
    }
}

void PhysicsWorld::resolveCircleCircle(Circle* c1, Circle* c2) {



    try {
        std::ofstream log("world_log.txt", std::ios::app);
        if (!log) {
            throw std::runtime_error("Kon world_log.txt niet openen");
        }
        log << "Collision detected: Circle '"
            << c1->getName() << "' with Circle '"
            << c2->getName() << "'\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Logging error: " << e.what() << "\n";
    }

    float dx = c2->getX() - c1->getX();
    float dy = c2->getY() - c1->getY();
    float dist2 = dx*dx + dy*dy;
    float rsum = c1->getRadius() + c2->getRadius();

    if (dist2 >= rsum * rsum || dist2 == 0.0f)
        return;

    float dist = std::sqrt(dist2);
    float penetration = rsum - dist;

    float nx = dx / dist;
    float ny = dy / dist;

    float m1 = c1->getMass();
    float m2 = c2->getMass();
    float total = m1 + m2;

    if (total <= 0.0f) return;

    c1->setX(c1->getX() - nx * (penetration * (m2 / total)));
    c1->setY(c1->getY() - ny * (penetration * (m2 / total)));
    c2->setX(c2->getX() + nx * (penetration * (m1 / total)));
    c2->setY(c2->getY() + ny * (penetration * (m1 / total)));

    float rvx = c2->getVX() - c1->getVX();
    float rvy = c2->getVY() - c1->getVY();
    float velAlongNormal = rvx * nx + rvy * ny;

    if (velAlongNormal > 0.0f)
        return;

    float j = -(1.0f) * velAlongNormal;
    j /= (1.0f / m1 + 1.0f / m2);

    float ix = j * nx;
    float iy = j * ny;

    c1->setVX(c1->getVX() - ix / m1);
    c1->setVY(c1->getVY() - iy / m1);
    c2->setVX(c2->getVX() + ix / m2);
    c2->setVY(c2->getVY() + iy / m2);
}

void PhysicsWorld::resolveBoxBox(Box* b1, Box* b2) {


    try {
        std::ofstream log("world_log.txt", std::ios::app);
        if (!log) {
            throw std::runtime_error("Kon world_log.txt niet openen");
        }
        log << "Collision detected: Box '"
            << b1->getName() << "' with Box '"
            << b2->getName() << "'\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Logging error: " << e.what() << "\n";
    }

    float left1   = b1->getX();
    float right1  = b1->getX() + b1->getWidth();
    float bottom1 = b1->getY();
    float top1    = b1->getY() - b1->getHeight();

    float left2   = b2->getX();
    float right2  = b2->getX() + b2->getWidth();
    float bottom2 = b2->getY();
    float top2    = b2->getY() - b2->getHeight();

    if (right1 <= left2 || right2 <= left1 || bottom1 <= top2 || bottom2 <= top1)
        return;

    float overlapX = std::min(right1 - left2, right2 - left1);
    float overlapY = std::min(bottom1 - top2, bottom2 - top1);

    if (overlapX < overlapY) {
        float half = overlapX * 0.5f;

        if (b1->getX() < b2->getX()) {
            b1->setX(b1->getX() - half);
            b2->setX(b2->getX() + half);
        } else {
            b1->setX(b1->getX() + half);
            b2->setX(b2->getX() - half);
        }
    } else {
        float half = overlapY * 0.5f;

        if (b1->getY() < b2->getY()) {
            b1->setY(b1->getY() - half);
            b2->setY(b2->getY() + half);
        } else {
            b1->setY(b1->getY() + half);
            b2->setY(b2->getY() - half);
        }
    }
}

void PhysicsWorld::resolveBoxCircle(Box* box, Circle* circle) {


    try {
        std::ofstream log("world_log.txt", std::ios::app);
        if (!log) {
            throw std::runtime_error("Kon world_log.txt niet openen");
        }
        log << "Collision detected: Box '"
            << box->getName() << "' with Circle '"
            << circle->getName() << "'\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Logging error: " << e.what() << "\n";
    }

    float closestX = std::clamp(circle->getX(), box->getX(), box->getX() + box->getWidth());
    float closestY = std::clamp(circle->getY(), box->getY() - box->getHeight(), box->getY());

    float dx = circle->getX() - closestX;
    float dy = circle->getY() - closestY;
    float dist2 = dx*dx + dy*dy;

    if (dist2 >= circle->getRadius() * circle->getRadius())
        return;

    float dist = std::sqrt(dist2);
    if (dist == 0.0f) { dx = 0.0f; dy = -1.0f; dist = 1.0f; }

    float penetration = circle->getRadius() - dist;
    float nx = dx / dist;
    float ny = dy / dist;

    circle->setX(circle->getX() + nx * penetration);
    circle->setY(circle->getY() + ny * penetration);

    float rvx = circle->getVX() - box->getVX();
    float rvy = circle->getVY() - box->getVY();
    float velAlongNormal = rvx * nx + rvy * ny;

    if (velAlongNormal > 0.0f)
        return;

    float m1 = circle->getMass();
    float m2 = box->getMass();

    float j = -(1.0f) * velAlongNormal;
    j /= (1.0f / m1 + 1.0f / m2);

    float ix = j * nx;
    float iy = j * ny;

    circle->setVX(circle->getVX() + ix / m1);
    circle->setVY(circle->getVY() + iy / m1);
    box->setVX(box->getVX() - ix / m2);
    box->setVY(box->getVY() - iy / m2);
}

const std::vector<Body*>& PhysicsWorld::getBodies() const {
    return bodies;
}
