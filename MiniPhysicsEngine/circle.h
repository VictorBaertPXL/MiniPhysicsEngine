#ifndef CIRCLE_H
#define CIRCLE_H

#include "body.h"

// vraag 3: correct class
// vraag 6: correct inheritance
// vraag 7: correct polymorphism
class Circle : public Body {
private:
    float radius;

public:
    Circle(float x, float y, float mass, float radius);

    float getRadius() const;

    void applyForces(float dt) override; // override van Body
};

#endif
