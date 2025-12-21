#ifndef CIRCLE_H
#define CIRCLE_H

#include "body.h"

class Circle : public Body {
private:
    float radius;

public:
    Circle()
        : Circle(0.0f, 0.0f, 1.0f, 10.0f)
    {}

    // const reference added
    Circle(float x, float y, float mass, const float& radius);

    Circle(const Circle& other)
        : Body(other),
        radius(other.radius)
    {}

    ~Circle() override {}

    inline float getRadius() const { return radius; }

    void applyForces(float dt = 1.0f) override;
};

#endif // CIRCLE_H
