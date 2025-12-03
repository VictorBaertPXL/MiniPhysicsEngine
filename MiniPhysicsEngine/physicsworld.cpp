#include "physicsworld.h"
#include "box.h"
#include "circle.h"
#include <algorithm>
#include <cmath>

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

// step: apply forces, integrate (with borders in Body::integrate), then collisions
void PhysicsWorld::step(float dt, int windowWidth, int windowHeight) {
    // 1) forces
    for (Body* body : bodies) {
        body->applyForces(dt);
    }

    // 2) integrate (body clamps to window basic edges)
    for (Body* body : bodies) {
        body->integrate(dt, windowWidth, windowHeight);
    }

    // 3) collisions
    handleCollisions();
}

// ---------------- Collision Handling ----------------
void PhysicsWorld::handleCollisions() {
    const size_t n = bodies.size();
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = i + 1; j < n; ++j) {
            Body* A = bodies[i];
            Body* B = bodies[j];

            // Circle–Circle
            if (Circle* c1 = dynamic_cast<Circle*>(A)) {
                if (Circle* c2 = dynamic_cast<Circle*>(B)) {
                    resolveCircleCircle(c1, c2);
                    continue;
                }
            }

            // Box–Box
            if (Box* b1 = dynamic_cast<Box*>(A)) {
                if (Box* b2 = dynamic_cast<Box*>(B)) {
                    resolveBoxBox(b1, b2);
                    continue;
                }
            }

            // Box–Circle (both orders)
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

// ---------------- Circle–Circle ----------------
void PhysicsWorld::resolveCircleCircle(Circle* c1, Circle* c2) {
    float dx = c2->getX() - c1->getX();
    float dy = c2->getY() - c1->getY();
    float dist2 = dx*dx + dy*dy;
    float rsum = c1->getRadius() + c2->getRadius();
    float rsum2 = rsum * rsum;

    if (dist2 >= rsum2 || dist2 == 0.0f) return; // no collision or coincident

    float dist = std::sqrt(dist2);
    float penetration = rsum - dist;

    // normal
    float nx = dx / dist;
    float ny = dy / dist;

    // position correction proportional to masses
    float m1 = c1->getMass();
    float m2 = c2->getMass();
    float total = m1 + m2;
    if (total <= 0.0f) return;

    // push them apart
    c1->setX(c1->getX() - nx * (penetration * (m2 / total)));
    c1->setY(c1->getY() - ny * (penetration * (m2 / total)));
    c2->setX(c2->getX() + nx * (penetration * (m1 / total)));
    c2->setY(c2->getY() + ny * (penetration * (m1 / total)));

    // relative velocity
    float rvx = c2->getVX() - c1->getVX();
    float rvy = c2->getVY() - c1->getVY();
    float velAlongNormal = rvx * nx + rvy * ny;
    if (velAlongNormal > 0) return; // moving apart

    // restitution
    float e = (c1->getRestitution() + c2->getRestitution()) * 0.5f;

    // impulse scalar
    float j = -(1.0f + e) * velAlongNormal;
    j /= (1.0f / m1 + 1.0f / m2);

    float ix = j * nx;
    float iy = j * ny;

    c1->setVX(c1->getVX() - ix / m1);
    c1->setVY(c1->getVY() - iy / m1);
    c2->setVX(c2->getVX() + ix / m2);
    c2->setVY(c2->getVY() + iy / m2);

    // friction (tangential)
    float tx = -ny;
    float ty = nx;
    float tvel = rvx * tx + rvy * ty;
    float mu = (c1->getFriction() + c2->getFriction()) * 0.5f;
    float jt = -tvel * mu;
    float fx = jt * tx;
    float fy = jt * ty;

    c1->setVX(c1->getVX() - fx / m1);
    c1->setVY(c1->getVY() - fy / m1);
    c2->setVX(c2->getVX() + fx / m2);
    c2->setVY(c2->getVY() + fy / m2);
}

// ---------------- Box–Box ----------------
void PhysicsWorld::resolveBoxBox(Box* b1, Box* b2) {
    float left1 = b1->getX();
    float right1 = b1->getX() + b1->getWidth();
    float bottom1 = b1->getY();
    float top1 = b1->getY() - b1->getHeight();

    float left2 = b2->getX();
    float right2 = b2->getX() + b2->getWidth();
    float bottom2 = b2->getY();
    float top2 = b2->getY() - b2->getHeight();

    if (right1 <= left2 || right2 <= left1 || bottom1 <= top2 || bottom2 <= top1) return;

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

        float e = (b1->getRestitution() + b2->getRestitution()) * 0.5f;
        float v1x = b1->getVX();
        float v2x = b2->getVX();
        float m1 = b1->getMass();
        float m2 = b2->getMass();
        float newV1x = (v1x*(m1 - e*m2) + (1+e)*m2*v2x) / (m1 + m2);
        float newV2x = (v2x*(m2 - e*m1) + (1+e)*m1*v1x) / (m1 + m2);

        b1->setVX(newV1x * (1.0f - b1->getFriction()));
        b2->setVX(newV2x * (1.0f - b2->getFriction()));
    } else {
        float half = overlapY * 0.5f;
        if (b1->getY() < b2->getY()) {
            b1->setY(b1->getY() - half);
            b2->setY(b2->getY() + half);
        } else {
            b1->setY(b1->getY() + half);
            b2->setY(b2->getY() - half);
        }

        float e = (b1->getRestitution() + b2->getRestitution()) * 0.5f;
        float v1y = b1->getVY();
        float v2y = b2->getVY();
        float m1 = b1->getMass();
        float m2 = b2->getMass();
        float newV1y = (v1y*(m1 - e*m2) + (1+e)*m2*v2y) / (m1 + m2);
        float newV2y = (v2y*(m2 - e*m1) + (1+e)*m1*v1y) / (m1 + m2);

        b1->setVY(newV1y * (1.0f - b1->getFriction()));
        b2->setVY(newV2y * (1.0f - b2->getFriction()));
    }
}

// ---------------- Box–Circle ----------------
void PhysicsWorld::resolveBoxCircle(Box* box, Circle* circle) {
    float closestX = std::clamp(circle->getX(), box->getX(), box->getX() + box->getWidth());
    float closestY = std::clamp(circle->getY(), box->getY() - box->getHeight(), box->getY());

    float dx = circle->getX() - closestX;
    float dy = circle->getY() - closestY;
    float dist2 = dx*dx + dy*dy;
    float r = circle->getRadius();
    if (dist2 >= r*r) return;

    float dist = std::sqrt(dist2);
    if (dist == 0.0f) { dx = 0.0f; dy = -1.0f; dist = 1.0f; }
    float penetration = r - dist;
    float nx = dx / dist;
    float ny = dy / dist;

    circle->setX(circle->getX() + nx * penetration);
    circle->setY(circle->getY() + ny * penetration);

    float e = (box->getRestitution() + circle->getRestitution()) * 0.5f;
    float rvx = circle->getVX() - box->getVX();
    float rvy = circle->getVY() - box->getVY();
    float velAlongNormal = rvx * nx + rvy * ny;
    if (velAlongNormal > 0) return;

    float m1 = circle->getMass();
    float m2 = box->getMass();
    float j = -(1.0f + e) * velAlongNormal;
    j /= (1.0f / m1 + 1.0f / m2);

    float ix = j * nx;
    float iy = j * ny;
    circle->setVX(circle->getVX() + ix / m1);
    circle->setVY(circle->getVY() + iy / m1);
    box->setVX(box->getVX() - ix / m2);
    box->setVY(box->getVY() - iy / m2);

    // friction
    float tx = -ny;
    float ty = nx;
    float tvel = rvx * tx + rvy * ty;
    float mu = (box->getFriction() + circle->getFriction()) * 0.5f;
    float jt = -tvel * mu;
    float fx = jt * tx;
    float fy = jt * ty;

    circle->setVX(circle->getVX() + fx / m1);
    circle->setVY(circle->getVY() + fy / m1);
    box->setVX(box->getVX() - fx / m2);
    box->setVY(box->getVY() - fy / m2);
}

// ---------------- Accessor ----------------
const std::vector<Body*>& PhysicsWorld::getBodies() const {
    return bodies;
}
