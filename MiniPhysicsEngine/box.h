#ifndef BOX_H
#define BOX_H

#include "body.h"

class Box : public Body {
private:
    float width;
    float height;

public:
    Box()
        : Box(0.0f, 0.0f, 1.0f, 10.0f, 10.0f)
    {}

    // const references added
    Box(float x, float y, float mass, const float& width, const float& height);

    Box(const Box& other)
        : Body(other),
        width(other.width),
        height(other.height)
    {}

    ~Box() override {}

    inline float getWidth() const { return width; }
    float getHeight() const;

    void applyForces(float dt = 1.0f) override;
};

#endif // BOX_H
