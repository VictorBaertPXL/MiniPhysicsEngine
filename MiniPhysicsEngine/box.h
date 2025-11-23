#ifndef BOX_H
#define BOX_H

#include "body.h"

// vraag 3: correct class
// vraag 6: correct inheritance
// vraag 7: correct polymorphism
class Box : public Body {
private:
    float width, height;

public:
    Box(float x, float y, float mass, float width, float height);

    float getWidth() const;
    float getHeight() const;

    void applyForces(float dt) override; // override van Body
};

#endif
